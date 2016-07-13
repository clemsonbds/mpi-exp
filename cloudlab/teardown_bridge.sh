#!/bin/bash

addr=`ifconfig|grep 10.10.1|tr ':' ' '|awk '{print $3}'`
iface=`ifconfig|grep 90:e2:ba|awk '{print $1}'`
#iface=`ifconfig | awk '/00:8c:fa/ {print $1}'`
bridge=br0

ip link del $bridge
ifconfig $iface $addr
