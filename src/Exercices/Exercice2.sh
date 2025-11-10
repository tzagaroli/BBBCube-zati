#!/usr/bin/env bash
# ------------------------------------------------------------------------------
# Exercice2.sh — H-KA Mechatronische Systeme (BBB)
#
# Automates the lab steps described in the instructions, staying as close as
# possible to the original console workflow:
# - GPIO66 (motor enable), GPIO67 (direction)
# - PWM: /sys/class/pwm/pwmchip7/pwm-7:1  (EHRPWM2B)
# - ADC:  /sys/bus/iio/devices/iio:device0 and /dev/iio:device0
#
# Flags (can be chained in one call, order respected):
#   -gpio-setup                 Initialize/export GPIO66/67 and set direction=out.
#                               (Sets gpio66=1 per the original 'echo 1 > value' test)
#   -stop-motor                 Disable motor (gpio66=0). Also safe-disable PWM (enable=0).
#   -start-motor                Enable PWM (enable=1) then free motor (gpio66=1).
#   -dir <0|1>                  Set direction (GPIO67 value).
#   -set-period <ns>            Set PWM period in nanoseconds (e.g., 20000000 for 50 Hz).
#                               PWM is temporarily disabled while changing period.
#   -set-dutycycle <val>        Set duty cycle; <val> can be "<ns>" or "<percent>%".
#                               Enforces 10%..90% for the driver (per the sheet).
#   -adc-setup                  Configure ADC (buffer off → enable channel 0 → buffer on).
#   -adc-dump                   Hex dump /dev/iio:device0 (current ADC buffered data).
#
# Usage examples:
#   ./Exercice2.sh -gpio-setup -stop-motor \
#                  -set-period 20000000 -set-dutycycle 10000000 \
#                  -start-motor
#
#   ./Exercice2.sh -stop-motor -set-dutycycle 20% -start-motor
#   ./Exercice2.sh -dir 0
#   ./Exercice2.sh -adc-setup -adc-dump
#
# Notes:
# - If available, 'config-pin' is used to mux P8_7/P8_8 as gpio and P8_13 as pwm.
# - Script must be run as root on the BBB (sysfs writes).
# ------------------------------------------------------------------------------

set -euo pipefail

# --- Constants from the instructions ------------------------------------------
GPIO_BASE="/sys/class/gpio"
GPIO_EN="/sys/class/gpio/gpio66"    # Motor enable (Freigabe)
GPIO_DIR="/sys/class/gpio/gpio67"   # Direction
PWMCHIP="/sys/class/pwm/pwmchip7"
PWMCHAN="$PWMCHIP/pwm-7:1"          # EHRPWM2B
IIO_DEV="/sys/bus/iio/devices/iio:device0"
IIO_NODE="/dev/iio:device0"

# --- Helpers ------------------------------------------------------------------
need_root() {
  if [[ "${EUID:-$(id -u)}" -ne 0 ]]; then
    echo "This script must run as root on the BBB." >&2
    exit 1
  fi
}

have_cmd() { command -v "$1" >/dev/null 2>&1; }

mux_pins_if_possible() {
  # Stay close to original: pinmux not explicitly in sheet.
  # If 'config-pin' exists, apply minimal mux to match the targets.
  if have_cmd config-pin; then
    # GPIO66 -> P8_7 ; GPIO67 -> P8_8 ; EHRPWM2B -> P8_13
    config-pin P8_7 gpio || true
    config-pin P8_8 gpio || true
    config-pin P8_13 pwm  || true
  fi
}

ensure_gpio_exported() {
  cd "$GPIO_BASE"
  [[ -d gpio66 ]] || echo 66 > export
  [[ -d gpio67 ]] || echo 67 > export
}

gpio_setup() {
  echo ">> GPIO setup (export + direction out + initial values)"
  ensure_gpio_exported
  echo out > "$GPIO_EN/direction"
  echo out > "$GPIO_DIR/direction"
  # Original sheet sets gpio66=1 for the quick test:
  echo 1 > "$GPIO_EN/value"
  # Direction initial (can be changed later via -dir):
  echo 1 > "$GPIO_DIR/value"
  echo "   gpio66(value)=$(cat "$GPIO_EN/value")  gpio67(value)=$(cat "$GPIO_DIR/value")"
}

stop_motor() {
  echo ">> Stop motor (disable PWM and clear enable GPIO)"
  if [[ -d "$PWMCHAN" ]]; then
    echo 0 > "$PWMCHAN/enable" || true
  fi
  if [[ -d "$GPIO_EN" ]]; then
    echo 0 > "$GPIO_EN/value" || true
  fi
}

start_motor() {
  echo ">> Start motor (enable PWM then set enable GPIO=1)"
  if [[ -d "$PWMCHAN" ]]; then
    echo 1 > "$PWMCHAN/enable"
  else
    echo "WARN: PWM channel not exported yet ($PWMCHAN). Did you run -set-period first?" >&2
  fi
  if [[ -d "$GPIO_EN" ]]; then
    echo 1 > "$GPIO_EN/value"
  else
    echo "WARN: GPIO66 not exported. Run -gpio-setup first." >&2
  fi
}

set_dir() {
  local v="${1:-}"
  [[ "$v" == "0" || "$v" == "1" ]] || { echo "Direction must be 0 or 1"; exit 2; }
  ensure_gpio_exported
  echo out > "$GPIO_DIR/direction"
  echo "$v" > "$GPIO_DIR/value"
  echo ">> Direction set to $v"
}

ensure_pwm_exported() {
  mkdir -p "$PWMCHIP"
  if [[ ! -d "$PWMCHAN" ]]; then
    echo ">> Export PWM channel 1 on $PWMCHIP"
    echo 1 > "$PWMCHIP/export"
    # Some kernels need a short settle
    sleep 0.05 || true
  fi
  [[ -d "$PWMCHAN" ]] || { echo "ERROR: $PWMCHAN not present after export"; exit 3; }
}

set_period_ns() {
  local ns="${1:-}"
  [[ "$ns" =~ ^[0-9]+$ ]] || { echo "Period must be an integer (nanoseconds)"; exit 2; }
  ensure_pwm_exported
  echo ">> Disable PWM to change period"
  echo 0 > "$PWMCHAN/enable" || true
  echo ">> Set polarity=normal (as per sheet)"
  echo normal > "$PWMCHAN/polarity"
  echo ">> Set period=${ns} ns"
  echo "$ns" > "$PWMCHAN/period"
}

get_period_ns() {
  if [[ -f "$PWMCHAN/period" ]]; then
    cat "$PWMCHAN/period"
  else
    echo ""
  fi
}

# Accepts "<ns>" or "<percent>%"
set_dutycycle() {
  local val="${1:-}"
  ensure_pwm_exported

  # Always disable before changing duty
  echo ">> Disable PWM to change duty cycle"
  echo 0 > "$PWMCHAN/enable" || true

  local period
  period="$(get_period_ns)"
  [[ -n "$period" ]] || { echo "ERROR: period not set. Use -set-period <ns> first."; exit 2; }

  local duty_ns=""
  if [[ "$val" =~ %$ ]]; then
    # Percentage mode: enforce 10..90%
    local pct="${val%%%}"
    [[ "$pct" =~ ^[0-9]+([.][0-9]+)?$ ]] || { echo "Invalid percent value: $val"; exit 2; }
    # Enforce driver constraint from the sheet
    awk -v P="$period" -v Q="$pct" '
      BEGIN{
        if (Q < 10 || Q > 90) { printf("ERROR: percent %.3f out of [10..90]\n", Q); exit 9; }
        printf("%d\n", int((Q/100.0)*P + 0.5));
      }' || exit 2
    duty_ns="$(awk -v P="$period" -v Q="$pct" 'BEGIN{printf("%d\n", int((Q/100.0)*P + 0.5))}')"
    echo ">> Duty from percent ${pct}% -> ${duty_ns} ns (period=${period} ns)"
  else
    # Nanoseconds mode
    [[ "$val" =~ ^[0-9]+$ ]] || { echo "Invalid duty value: use <ns> or <percent>%"; exit 2; }
    duty_ns="$val"
    # Also check 10..90% constraint if we can compute it
    awk -v P="$period" -v D="$duty_ns" '
      BEGIN{
        if (D<=0 || D>=P) { print "ERROR: duty must be in (0, period)"; exit 9; }
        pct = (100.0*D)/P;
        if (pct < 10 || pct > 90) {
          printf("ERROR: derived percent %.3f out of [10..90]\n", pct);
          exit 9;
        }
      }' || exit 2
    echo ">> Duty set to ${duty_ns} ns (validated 10..90% of period=${period} ns)"
  fi

  echo "$duty_ns" > "$PWMCHAN/duty_cycle"
  echo ">> Duty written. You can -start-motor to enable output."
}

adc_setup() {
  echo ">> ADC setup (buffer off → enable channel 0 → buffer on)"
  cd "$IIO_DEV"
  echo 0 > buffer/enable
  echo 1 > scan_elements/in_voltage0_en
  echo 1 > buffer/enable
  echo "   ADC buffer enabled on channel 0."
}

adc_dump() {
  echo ">> Dumping /dev/iio:device0 (hex). Stop with Ctrl+C."
  if have_cmd hd; then
    hd "$IIO_NODE"
  else
    hexdump -C "$IIO_NODE"
  fi
}

usage() {
  cat <<EOF
Usage: $0 [flags in sequence]
  -gpio-setup                 Export and configure GPIO66/67 as outputs; set gpio66=1, gpio67=1
  -stop-motor                 gpio66=0 and PWM enable=0
  -start-motor                PWM enable=1 then gpio66=1
  -dir <0|1>                  Set direction pin (GPIO67)
  -set-period <ns>            Set PWM period (nanoseconds), e.g., 20000000 for 50 Hz
  -set-dutycycle <val>        Set duty cycle in "<ns>" or "<percent>%". Enforces 10..90%
  -adc-setup                  Configure ADC channel 0 (buffered)
  -adc-dump                   Hex-dump /dev/iio:device0

Examples:
  $0 -gpio-setup -stop-motor -set-period 20000000 -set-dutycycle 20% -start-motor
  $0 -dir 0
  $0 -stop-motor -adc-setup -adc-dump
EOF
}

# --- Main ---------------------------------------------------------------------
need_root
mux_pins_if_possible

if [[ $# -eq 0 ]]; then
  usage
  exit 0
fi

while [[ $# -gt 0 ]]; do
  case "$1" in
    -gpio-setup)      gpio_setup; shift ;;
    -stop-motor)      stop_motor; shift ;;
    -start-motor)     start_motor; shift ;;
    -dir)             shift; set_dir "${1:-}"; shift ;;
    -set-period)      shift; set_period_ns "${1:-}"; shift ;;
    -set-dutycycle)   shift; set_dutycycle "${1:-}"; shift ;;
    -adc-setup)       adc_setup; shift ;;
    -adc-dump)        adc_dump; shift ;;
    -h|--help)        usage; exit 0 ;;
    *) echo "Unknown flag: $1"; usage; exit 2 ;;
  esac
done
