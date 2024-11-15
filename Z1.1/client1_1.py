import socket
import sys
import argparse


def end(s):
    print("end of work")
    s.close()


def send_data(s, msg):
    try:
        s.sendto(str.encode(msg), (HOST, PORT))
        print(f"sent message len = {len(msg)}")
    except WindowsError as e:
        return -2, len(msg)
    response = ""
    while not response:
        try:
            response, server_addr = s.recvfrom(1024)
            print(f"Server response: {response!r}")
            if int(response) != len(msg):
                print("verification error")
                end(s)
            return 0, int(response)
        except socket.timeout:
            print("socket timeout")
            end(s)


def setup():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((HOST, PORT))
    print("created socket")
    x = 2
    x_o = -1
    a = 2
    r = 0
    s.settimeout(10)
    while abs(x -x_o)>1:
        msg = "A"*x
        if x >=3:
            msg = "z32" + "A"*(x-3)
        res, r = send_data(s, msg)
        if(x==r):
            if res == -2:
                x = int(x - (x- x_o)/2)
                continue
            else:
                x_o = x
                x = int(x*a)
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
    setup()


if __name__ == "__main__":
    main(sys.argv)
