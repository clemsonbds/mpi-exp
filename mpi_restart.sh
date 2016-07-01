#!/bin/bash

bridge=br0

docker kill mpi
docker rm mpi
docker run --net=none --name mpi -d rakurai/openmpi
sudo pipework $bridge mpi 10.10.1.100/24

for i in `seq 1 8`; do
  ip=10.10.1.10$i
  name=mpi-$i
  ssh node-$i "docker kill mpi; docker rm mpi; docker pull rakurai/openmpi; docker run --net=none -h $name --name mpi -d rakurai/openmpi; sudo pipework $bridge mpi $ip/24" &
done

