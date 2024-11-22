import socket
import sys
import argparse


def end(s):
    print("end of work")
    s.close()


def send_data(s, msg):
    try:
        s.sendto(msg.encode(), (HOST, PORT))
        print(f"sent message of length = {len(msg)}")
    except OSError as e:
        return -2, len(msg)

    response = ""
    while not response:
        try:
            response, server_addr = s.recvfrom(1024)
            print(f"server response: {response!r}")
            try:
                response = int(response)
            except ValueError:
                response = len(msg)
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
    s.settimeout(10)

    # Fixed-length message
    msg_size = 512
    payload = "A" * (msg_size - 3)  # Fill the rest of the datagram
    msg = "z32" + payload

    while True:
        res, r = send_data(s, msg)
        if res == -2:
            print("failed to send message, retrying...")
            continue

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
