import socket
import argparse
import sys


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


def main(arguments):
    parser = argparse.ArgumentParser()
    parser.add_argument("--IP", type=str)
    parser.add_argument("--PORT", type=int)
    args = parser.parse_args(arguments[1:])
    global HOST
    global PORT
    if not args.IP:
        HOST = "127.0.0.1"
    else:
        HOST = args.IP
    if not args.PORT:
        PORT = 3201
    else:
        PORT = args.PORT
    recv_data()


if __name__ == "__main__":
    main(sys.argv)