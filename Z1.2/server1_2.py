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

    expected_size = 512  # Fixed packet size
    print(f"server listening on {HOST}:{PORT}")

    try:
        while True:
            try:
                data, ret_addr = s.recvfrom(expected_size + 33)
            except socket.timeout:
                print("socket timeout")
                break

            # Verify packet size
            size_rec = sys.getsizeof(data) - 33
            if size_rec != expected_size:
                print(f"unexpected packet size: {size_rec} bytes (expected {expected_size})")
                continue

            if data[:3] != b"z32":
                print("error: missing or incorrect prefix")
                continue

            print(f"received {size_rec} bytes from {ret_addr}")

            s.sendto(str.encode(f"{size_rec}"), ret_addr)

    except Exception as e:
        print(f"an error occurred: {e}")
    finally:
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
