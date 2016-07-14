#!/bin/bash
nruns=$1
COUNTER=0
while [ $COUNTER -lt $nruns ];
	do
	mpirun --np 128 --mca btl_tcp_if_include 10.10.1.0/24 --bynode --machinefile machinefile hpcc
	let COUNTER=COUNTER+1
	echo TEST NUMBER $COUNTER DONE
done

