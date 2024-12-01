#!/bin/bash

docker build -t z32_server_image ./server
docker build -t z32_client_image ./client

docker run --rm -d -it --network-alias z32_server --ip '172.21.32.3' --network z32_network --name z32_server z32_server_image > result_server.txt
docker logs -f z32_server > result_server.txt 2>&1 &
docker run --rm -it --network-alias z32_client --ip '172.21.32.2' --network z32_network --name z32_client z32_client_image 100 > result_client.txt
