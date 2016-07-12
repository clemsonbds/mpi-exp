#!/bin/bash
nruns=$1
COUNTER=0
while [ $COUNTER -lt $nruns ];
	do
	mpirun --np 128 --bynode --machinefile ../machinefile hpcc
	let COUNTER=COUNTER+1
	echo TEST NUMBER $COUNTER DONE
done

