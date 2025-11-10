#!/usr/bin/env bash
# ------------------------------------------------------------------------------
# send_to_bbb.sh
#
# Copy a local file or the FULL CONTENT of a local directory to a BeagleBone
# over SSH (root@localhost -p48000) into a target directory (default /root/zati1012).
#
# Behavior:
#   - If input is a FILE:
#       1) Create the remote target directory if missing.
#       2) Truncate the remote file to zero bytes (ensures old content is gone).
#       3) Upload the local file via scp.
#
#   - If input is a DIRECTORY:
#       Preferred: use rsync to mirror the CONTENTS (includes dotfiles) with --delete
#       Fallback : use tar over SSH (removes existing content first, then extracts).
#
# Usage:
#   ./send_to_bbb.sh <local_path_file_or_directory> [remote_target_dir]
#
# Examples:
#   ./send_to_bbb.sh ./main.cpp                 # -> /root/zati1012/main.cpp
#   ./send_to_bbb.sh ./my_project               # -> sync ./my_project/* to /root/zati1012/
#   ./send_to_bbb.sh ./my_project /root/workdir # -> sync to /root/workdir/
#
# Exit codes:
#   0 = success
#   1 = usage error
#   2 = local path not found
#   3 = local path is neither file nor directory
#   4 = required tool missing (scp/ssh or tar)
# ------------------------------------------------------------------------------

set -euo pipefail

# --- Connection defaults (adjust if needed) -----------------------------------
HOST="localhost"
PORT="48000"
USER="root"
DEFAULT_REMOTE_DIR="/root/zati1012"

# --- Helper: print usage and exit ---------------------------------------------
usage() {
  echo "Usage: $0 <local_path_file_or_directory> [remote_target_dir]"
  echo
  echo "Copies a local file or the CONTENT of a local directory to the BeagleBone."
  echo "SSH endpoint: ${USER}@${HOST} -p ${PORT}"
  echo "Default remote target directory: ${DEFAULT_REMOTE_DIR}"
  exit 1
}

# --- Parse args ----------------------------------------------------------------
LOCAL_PATH="${1:-}"
[[ -z "${LOCAL_PATH}" ]] && usage
REMOTE_DIR="${2:-$DEFAULT_REMOTE_DIR}"

# --- Sanity checks -------------------------------------------------------------
if [[ ! -e "$LOCAL_PATH" ]]; then
  echo "Error: local path not found: $LOCAL_PATH" >&2
  exit 2
fi

# Ensure required commands exist
need_cmd() { command -v "$1" >/dev/null 2>&1 || { echo "Error: '$1' is required." >&2; exit 4; }; }
need_cmd ssh
need_cmd scp
# rsync and tar are optional; we check them conditionally later

# --- FILE path: truncate then upload ------------------------------------------
if [[ -f "$LOCAL_PATH" ]]; then
  BASENAME="$(basename "$LOCAL_PATH")"

  echo ">> Ensuring remote directory exists: ${REMOTE_DIR}"
  ssh -p"$PORT" "$USER@$HOST" "mkdir -p -- '$(printf %q "$REMOTE_DIR")'"

  echo ">> Truncating remote file to zero bytes: ${REMOTE_DIR}/${BASENAME}"
  ssh -p"$PORT" "$USER@$HOST" ": > '$(printf %q "$REMOTE_DIR")/$(printf %q "$BASENAME")'"

  echo ">> Uploading file via scp..."
  scp -P "$PORT" -- "$LOCAL_PATH" "$USER@$HOST:$REMOTE_DIR/"

  echo "✅ File uploaded to: $REMOTE_DIR/$BASENAME"
  exit 0
fi

# --- DIRECTORY path: mirror CONTENTS ------------------------------------------
if [[ -d "$LOCAL_PATH" ]]; then
  echo ">> Ensuring remote directory exists: ${REMOTE_DIR}"
  ssh -p"$PORT" "$USER@$HOST" "mkdir -p -- '$(printf %q "$REMOTE_DIR")'"

  if command -v rsync >/dev/null 2>&1; then
    echo ">> Using rsync to mirror directory CONTENTS (includes dotfiles) with --delete"
    # Trailing slashes matter: LOCAL_PATH/ -> copies CONTENTS into REMOTE_DIR/
    rsync -avz --delete -e "ssh -p $PORT" -- "$LOCAL_PATH"/ "$USER@$HOST:$REMOTE_DIR"/
    echo "✅ Directory contents synchronized to: $REMOTE_DIR/ (rsync --delete)"
    exit 0
  fi

  # Fallback to tar over SSH if rsync is not available
  need_cmd tar
  echo ">> rsync not available. Falling back to tar over SSH."
  echo ">> Removing existing remote content first (keeps the directory itself)..."
  # Remove normal files and dotfiles (.[!.]* and ..?*) but ignore '.' and '..'
  ssh -p"$PORT" "$USER@$HOST" "rm -rf -- '$(printf %q "$REMOTE_DIR")'/* '$(printf %q "$REMOTE_DIR")'/.[!.]* '$(printf %q "$REMOTE_DIR")'/..?* 2>/dev/null || true"

  echo ">> Streaming tar to remote..."
  tar -C "$LOCAL_PATH" -cf - . | ssh -p"$PORT" "$USER@$HOST" "tar -C '$(printf %q "$REMOTE_DIR")' -xpf -"

  echo "✅ Directory contents transferred to: $REMOTE_DIR/ (tar fallback)"
  exit 0
fi

echo "Error: '$LOCAL_PATH' is neither a file nor a directory." >&2
exit 3
