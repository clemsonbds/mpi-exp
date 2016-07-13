#!/bin/bash

addr=`ifconfig|grep 10.10.1|tr ':' ' '|awk '{print $3}'`
iface=`ifconfig|grep 90:e2:ba|awk '{print $1}'`
#iface=`ifconfig | awk '/10.10.1/ {print $1}' RS="\n\n"`
bridge=br0

ip link add name $bridge type bridge
ip link set $bridge up
ip link set $iface master $bridge

ip link add tap1 type veth peer name br-tap1
ip link set br-tap1 master $bridge
ip link set tap1 up
ip link set br-tap1 up

ifconfig tap1 $addr
ifconfig $iface 0
