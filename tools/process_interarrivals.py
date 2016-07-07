#!/usr/bin/python

import sys
import to_interarrivals
import to_bins

if __name__ == "__main__":
	filename = sys.argv[1]

	if (len(sys.argv) > 2):
		bin_size_us = float(sys.argv[2])
	else:
		bin_size_us = 10

	timestamps = []
	with open(sys.argv[1]) as f:
		for line in f.readlines():
			sec, usec = line.split('.')
			if len(usec) < 7:
				usec = '0'*(7-len(usec)) + usec
			timestamps.append(float(sec + '.' + usec)*1000000)

	interarrivals = to_interarrivals.to_interarrivals(timestamps)
	bins = to_bins.to_bins(interarrivals, bin_size_us)

	sum = len(interarrivals)
	for key in sorted(bins.keys()):
		print key*bin_size_us, (key+1)*bin_size_us, bins[key], float(bins[key])/sum*100
