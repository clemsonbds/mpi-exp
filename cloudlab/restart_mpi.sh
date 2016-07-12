#!/bin/bash

bridge=br0
nodenum=`hostname | tr '.' ' ' | tr '-' ' ' | awk '{print $2}'`
mpihostname=mpi-$nodenum
ip=10.10.1.10${nodenum}

docker kill mpi
docker rm mpi
docker pull rakurai/openmpi
docker run --net=none --name mpi -h $mpihostname -d rakurai/openmpi
sudo pipework $bridge mpi ${ip}/24


