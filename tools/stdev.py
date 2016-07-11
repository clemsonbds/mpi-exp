#!/usr/bin/python

import sys

def online_variance(data):
    n = 0
    mean = 0.0
    M2 = 0.0
     
    for x in data:
        n += 1
        delta = x - mean
        mean += delta/n
        M2 += delta*(x - mean)

    print n, mean, M2

    if n < 2:
        return float('nan')
    else:
        return mean, M2 / (n - 1)

with open(sys.argv[1]) as f:
	times = []
	interarrivals = []

	for line in f.readlines():
		ts = line.split()[0]
		hour, min, sec = ts.split(":")
		ts_sec = int(hour)*3600 + int(min)*60 + float(sec)
		times.append(ts_sec)

for i in range(1, len(times)):
	interarrivals.append(times[i] - times[i-1])

#print interarrivals
import numpy
#mean, variance = online_variance(interarrivals)
print "n = %d, mean = %f, stdev = %f" % (len(interarrivals), numpy.mean(interarrivals), numpy.std(interarrivals))
