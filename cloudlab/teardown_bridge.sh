#!/bin/bash

addr=`ifconfig|grep 10.10.1|tr ':' ' '|awk '{print $3}'`
iface=`ifconfig | awk '/00:8c:fa/ {print $1}'`
bridge=br0

ip link delete $bridge type bridge
ifconfig $iface $addr
