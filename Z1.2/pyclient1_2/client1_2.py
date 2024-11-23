import socket
import sys
import argparse


def end(s):
    s.close()
    print("end of work")
    exit(0)



def send_data(s, msg, n):
    s.sendto(msg.encode(), (HOST, PORT))
    print(f"sent message of length = {len(msg)}")
    response = ""
    print("waiting")
    while not response:
        try:
            response, server_addr = s.recvfrom(1024)
            print(f"server response: {response!r}")
            # revive in format ACK{packet num}
            try:
                packet_num = int(response[3:6])
                if packet_num != n:
                    print(f"received {packet_num} does not equal sent {n}")
                    return -1
            except ValueError:
                print("incorrect response format : packet number")
                end(s)
            if(response[:3] == b"MIS"):
                print(f"packet {packet_num} have not arrived!")
                return -3
            elif(response[:3] != b"ACK"):
                print("incorrect response format : ACK")
                end(s)
        except socket.timeout:
            print("socket timeout")
            return -2
        return 0


def setup():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((HOST, PORT))
    print("created socket")
    s.settimeout(10)

    # Fixed-length message
    msg_size = 512
    payload = "A" * (msg_size - 10)


    # send 20 packets
    n = 1
    timeout= 0
    while n <= 20:
        if timeout > 10:
            print("server not responding, aborting")
            end(s)
        msg = "packet" + str(n).zfill(3) + ' ' + payload
        res = send_data(s, msg, n)
        if res == -1:
            print("failed verification, retrying...")
            continue
        if res == -2:
            print("did not receive confirmation, retrying...")
            timeout += 1
            continue
        if res == -3:
            print("re-sending missing packet")
            n -= 1
            continue
        timeout = 0
        n+=1



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
