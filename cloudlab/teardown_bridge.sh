#!/bin/bash

addr=`ifconfig|grep 10.10.1|tr ':' ' '|awk '{print $3}'`
iface=`ifconfig | awk '/34:17:eb/ {print $1}'`
bridge=br0

ip link delete $bridge type bridge
ifconfig $iface $addr
