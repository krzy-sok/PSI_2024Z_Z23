#!/bin/bash

echo all result files will be created in z32_results directory
echo python to python demonstration, results in server_py.txt and client_py.txt

rm -r z32_results
mkdir z32_results

server_id="$(docker run -it -d --network z32_network --hostname z32_server --network-alias z32_server_py --name z32_server_py z32_server_py --IP z32_server_py)"
client_id="$(docker run -it -d --network z32_network --hostname z32_client_py --network-alias z32_client_py --name z32_client_py z32_client_py --IP z32_server_py)"

docker logs --since=1h ${server_id} > ./z32_results/server_py.txt
docker logs --since=1h ${client_id} > ./z32_results/client_py.txt

docker rm z32_client_py
docker rm z32_server_py


echo c++ to c++ demonstration, results in server_cpp.txt and client_cpp.txt

server_id="$(docker run -it --rm --network-alias z32_server --ip '172.21.32.2' --network z32_network --name z32_server z32_server)"
client_id="$(docker run -it --network-alias z32_client --ip '172.21.32.3' --network z32_network --name z32_client z32_client)"

docker logs --since=1h ${server_id} > ./z32_results/server_cpp.txt
docker logs --since=1h ${client_id} > ./z32_results/client.cpp.txt

# echo c++ to python and vice versa, results in cross_server_cpp, cross_client_py etc...
