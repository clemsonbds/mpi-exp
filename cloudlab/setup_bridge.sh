#!/bin/bash

addr=`ifconfig|grep 10.10.1|tr ':' ' '|awk '{print $3}'`
iface=`ifconfig|grep 90:e2:ba|awk '{print $1}'`
#iface=`ifconfig | awk '/10.10.1/ {print $1}' RS="\n\n"`
bridge=br0

ip link add name $bridge type bridge
ip link set $bridge up
ip link set $iface master $bridge

ifconfig $bridge $addr
ifconfig $iface 0
