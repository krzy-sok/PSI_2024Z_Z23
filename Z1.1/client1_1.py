import socket
import os

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 3201  # The port used by the server

def end(s):
    print("end of work")
    s.close()

def send_data(s, msg):
    s.sendto(str.encode(msg), (HOST, PORT))
    print(f"sent message len = {len(msg)}")
    response = ""
    while not response:
        try:
            response, server_addr = s.recvfrom(1024)
            # print("server confirmation : {data}")
            print(f"Server response: {response!r}")
            if int(response) != len(msg):
                print("verification error")
                return -2
                # end(s)
        except socket.timeout:
            print("socket timeout")
            return -1
        except WindowsError as e:
            print("no kurwa")
            print(e)
            return -2

def setup():
    # with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(10)
    s.connect((HOST, PORT))
    print("created socket")
    # s.connect((HOST, PORT))
    x = 2
    x_o = -1
    # while abs(x - x_o) > 1:
    # if verificarion good x = x + (x_max - x)/2
    # else x = x - (x_max - x)/2
    # for msg in messages:
    while abs(x -x_o)>1:
        msg = "A"*x
        res = send_data(s, msg)
        if res == -1:
            end(s)
        elif res == -2:
            x = x - (x- x_o)/2
        else:
            x_o = x
            x = x*2

    end(s)


# send_data()
setup()
# if main
# get args - ip, port
# send_data