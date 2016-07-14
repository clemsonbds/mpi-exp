#!/bin/bash
COUNTER=0
nruns=1
type=$2
prg=$1
while [ $COUNTER -lt $nruns ];
	do
	mpirun --np 128 --mca btl_tcp_if_include 10.10.1.0/24 --bynode --machinefile machinefile ${prg} > ${prg}.${type}.txt

	let COUNTER=COUNTER+1
	echo TESTS DONE
done

