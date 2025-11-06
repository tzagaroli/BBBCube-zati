import socket
import struct
import threading

class ServoClient:
    def __init__(self, host="localhost", port=40001, timeout=2.0):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.sock = None
        self.lock = threading.Lock()

        # Event Mapping
        self.EEvent = {
            "DefaultIgnore": 0,
            "Set90Deg": 1,
            "Set10Deg": 2,
            "Set0Deg": 3,
            "SetM10Deg": 4,
            "SetM90Deg": 5,
            "Set_5deg_gap": 6,
            "Set_release": 7
        }

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(self.timeout)
        try:
            self.sock.connect((self.host, self.port))
            print(f"[ServoClient] Verbunden zu {self.host}:{self.port}")
        except Exception as e:
            print(f"[ServoClient] Verbindung fehlgeschlagen: {e}")
            self.sock = None

    def disconnect(self):
        if self.sock:
            self.sock.close()
            self.sock = None
            print("[ServoClient] Verbindung geschlossen")

    def send_event(self, event_name):
        if not self.sock:
            print("[ServoClient] Nicht verbunden!")
            return
        if event_name not in self.EEvent:
            print(f"[ServoClient] Ungültiges Event: {event_name}")
            return

        message = struct.pack("<I64s", self.EEvent[event_name], b"\x00"*64)
        try:
            with self.lock:  # Thread-safe
                self.sock.sendall(message)
            print(f"[ServoClient] Event '{event_name}' gesendet")
        except Exception as e:
            print(f"[ServoClient] Fehler beim Senden: {e}")