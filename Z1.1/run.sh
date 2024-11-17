#!/bin/bash

echo all result files will be created in z32_results directory

rm -r z32_results
mkdir z32_results


echo c to c demonstration, results in server_c.txt and client_c.txt

server_id="$(docker run -it -d --network-alias z32_server --ip '172.21.32.2' --network z32_network --name z32_server z32_server)"
client_id="$(docker run -it -d --network-alias z32_client --ip '172.21.32.3' --network z32_network --name z32_client z32_client)"

docker logs --since=1h ${server_id} > ./z32_results/server_c.txt
docker logs --since=1h ${client_id} > ./z32_results/client_c.txt



echo python to python demonstration, results in server_py.txt and client_py.txt

server_id="$(docker run -it -d --network z32_network --hostname z32_server --network-alias z32_server_py --name z32_server_py z32_server_py --IP z32_server_py)"
client_id="$(docker run -it -d --network z32_network --hostname z32_client_py --network-alias z32_client_py --name z32_client_py z32_client_py --IP z32_server_py)"


docker logs --since=1h ${server_id} > ./z32_results/server_py.txt
docker logs --since=1h ${client_id} > ./z32_results/client_py.txt

sleep 10

docker rm z32_client_py
docker rm z32_server_py
docker rm z32_client
docker rm z32_server

echo c to python and vice versa, results in cross_server_cpp, cross_client_py etc...

# do stuff

server_id="$(docker run -it -d --network-alias z32_server --ip '172.21.32.2' --network z32_network --name z32_server z32_server)"
client_id="$(docker run -it -d --network z32_network --hostname z32_client_py --network-alias z32_client_py --name z32_client_py z32_client_py --IP '172.21.32.2' --PORT 8080)"

docker logs --since=1h ${server_id} > ./z32_results/cross_server_c.txt
docker logs --since=1h ${client_id} > ./z32_results/cross_client_py.txt

sleep 10

docker rm z32_client_py
docker rm z32_server

server_id="$(docker run -it -d --network z32_network --hostname z32_server --network-alias z32_server_py --ip '172.21.32.2' --name z32_server_py z32_server_py --IP z32_server_py --PORT 8080)"
client_id="$(docker run -it -d --network-alias z32_client --ip '172.21.32.3' --network z32_network --name z32_client z32_client)"

docker logs --since=1h ${server_id} > ./z32_results/cross_server_py.txt
docker logs --since=1h ${client_id} > ./z32_results/cross_client_c.txt

sleep 10

docker rm z32_server_py
docker rm z32_client


echo end of work