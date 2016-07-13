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

	times = []
	with open(sys.argv[1]) as f:
		for line in f.readlines():
			time = float(line)
			times.append((int)(time*1000000))

	bins = to_bins.to_bins(times, bin_size_us)

	sum = len(times)
	for key in sorted(bins.keys()):
		print key*bin_size_us, (key+1)*bin_size_us, bins[key], float(bins[key])/sum*100
