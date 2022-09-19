
import socket
import time

def bitstring_to_bytes(s):
    v = int(s, 2)
    b = bytearray()
    while v:
        b.append(v & 0xff)
        v >>= 8
    return bytes(b[::-1])

s = socket.socket(socket.AF_INET)
s.connect(('127.0.0.1', 1234))

time.sleep(1)
s.send(bitstring_to_bytes("00100001"))

time.sleep(10)
print("Yeah! I'm connected")