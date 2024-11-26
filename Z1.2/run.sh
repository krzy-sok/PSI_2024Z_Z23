#!/bin/bash

docker compose build
docker compose up > result1_2.txt &
sleep 3
#docker ps | grep "z32"
docker exec z32_client1_2 tc qdisc add dev eth0 root netem delay 1000ms 500ms loss 33%