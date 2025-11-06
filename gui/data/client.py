import socket

class TCPClient:
    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.sock = None

    def connect(self):
        try:
            self.sock = socket.create_connection((self.host, self.port))
            print(f"Connected to {self.host}:{self.port}")
            return True
        except Exception as e:
            print(f"Failed to connect: {e}")
            return False


    def recv_bytes(self, num_bytes: int) -> bytes:
        if self.sock is None:
            raise RuntimeError("Socket not connected")
        data = b''
        while len(data) < num_bytes:
            chunk = self.sock.recv(num_bytes - len(data))
            if not chunk:
                raise ConnectionError("Connection lost")
            data += chunk
        return data

    def close(self):
        if self.sock:
            self.sock.close()
            print("Connection closed")