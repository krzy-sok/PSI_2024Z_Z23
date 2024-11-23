import socket
import argparse
import sys
import time


def end(s):
    print("end of work")
    s.close()


def recv_data():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(12)
    s.bind((HOST, PORT))

    expected_size = 512  # Fixed packet size
    print(f"server listening on {HOST}:{PORT}")
    last_packet = 0
    try:
        while True:
            # for testing unexpected connection break
            # if last_packet > 2:
            #     time.sleep(120)
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

            if data[:6] != b"packet":
                print("error: missing or incorrect prefix")
                continue
            cur_packet = int(data[6:9])
            if cur_packet <= last_packet:
                print("incorrect packet number")
                continue
            if cur_packet > last_packet+1:
                print(f"packet {last_packet+1} lost!")
                s.sendto(str.encode(f"MIS{last_packet+1}"), ret_addr)
                continue
            print(f"packet {data[0:9]} verified")
            last_packet = int(data[6:9])
            print(f"received {size_rec} bytes from {ret_addr}")
            s.sendto(str.encode(f"ACK{last_packet}"), ret_addr)

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
