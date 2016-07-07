#!/usr/bin/python

import sys

def to_bins(elements, bin_range, mn=sys.maxint, mx = 0):
	if (mn > mx):
		for e in elements:
			if e < mn: mn = e
			if e > mx: mx = e

	bins = {}
	for i in range(int(mn/bin_range), int(mx/bin_range)+1):
		bins[i] = 0

	for e in elements:
		bins[int(e/bin_range)] += 1

	return bins

if __name__ == "__main__":
	filename = sys.argv[1]

	if (len(sys.argv) > 2):
		bin_size_us = float(sys.argv[2])
	else:
		bin_size_us = 10

	interarrivals = []
	mn = sys.maxint
	mx = 0

	with open(sys.argv[1]) as f:
		for line in f.readlines():
			t = int(line)

			if t < mn:
				mn = t
			if t > mx:
				mx = t

			interarrivals.append(t) # to microseconds

	bins = to_bins(interarrivals, bin_size_us, mn, mx)
	sum = len(interarrivals)

	for key in sorted(bins.keys()):
		print key*bin_size_us, (key+1)*bin_size_us, bins[key], float(bins[key])/sum*100

	import numpy
	print "mean %f, stdev %f" % (numpy.mean(interarrivals), numpy.std(interarrivals))
