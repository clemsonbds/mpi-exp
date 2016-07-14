#!/usr/bin/python

import sys

names = []
min_bin = sys.maxint
max_bin = 0
interval = 0

counts = {}

for filename in sys.argv[1:]:
	name = filename.rsplit('.')[0]
	names.append(name)
	counts[name] = {}

	with open(filename) as f:
		for line in f.readlines():
			lowbin, highbin, count, percent = line.split()
			lowbin = int(lowbin)
			highbin = int(highbin)
			if lowbin < min_bin:
				min_bin = lowbin
			if highbin > max_bin:
				max_bin = highbin
			if interval == 0:
				interval = highbin - lowbin
			
			counts[name][lowbin] = int(count)			

for bin in range(min_bin, max_bin, interval):
	s = str(bin)
	for name in names:
		if bin in counts[name]:
			s += '\t' + str(counts[name][bin])
		else:
			s += '\t0'
#	print bin + '\t'.join([count for counts[name][bin] in names])
	print s
