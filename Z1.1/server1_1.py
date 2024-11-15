import socket
import time
import sys

HOST = "127.0.0.1"
PORT = 3201


def end(s):
    print("end of work")
    s.close()

def recv_data():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(10)
    s.bind((HOST, PORT))

    size = 100000
    data_o = str.encode("")
    print(f"overhead {sys.getsizeof(data_o)} bytes")
    while True:
        try:
            data, ret_addr = s.recvfrom(size)
        except socket.timeout:
            print("socket timeout")
            break
        # check data
        # change to short ack with ammount of data recieved
        if data != data_o:
            # 33 bytes overhead
            size_rec = sys.getsizeof(data)-33
            if size_rec >= 3:
                data_list = list(data)
                # check ascii code of firs 3 chars
                if data_list[0:3] != [ord('z'), ord('3'), ord('2')]:
                    print("error reading message")
                    end(s)
            print(f"recieved {size_rec} bytes")
            s.sendto(str.encode(f"{size_rec}"), ret_addr)
        data_o = data
    end(s)

recv_data()


# if main
# gest args - ip port
# recive_data