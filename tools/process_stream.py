#!/usr/bin/python

import sys
import to_bins
import stats
import numpy

filename=sys.argv[1]
resolution = int(sys.argv[2])
filename_root = filename.rsplit('.')[0]

statnames = ['send', 'recv', 'delay']
data = {}
for name in statnames:
	data[name] = {'intervals':[]}

with open(filename) as f:
	for line in f.readlines():
		sint, rint = line.split()
		sint = int(sint)
		rint = int(rint)
		data['send']['intervals'].append(sint)
		data['recv']['intervals'].append(rint)
		data['delay']['intervals'].append(rint-sint)

for name in statnames:
	mn = min(data[name]['intervals'])
	mx = max(data[name]['intervals'])
	bins = to_bins.to_bins(data[name]['intervals'], resolution, mn, mx)
	autocorr = stats.acf(data[name]['intervals'], 30)
	mean = numpy.mean(data[name]['intervals'])
	stdev = numpy.std(data[name]['intervals'])
	n = len(data[name]['intervals'])

	with open(filename_root + '.' + name + '.bins.txt', 'w') as f:
		for key in sorted(bins.keys()):
			print >>f, "%d\t%d\t%d\t%f" % (key*resolution, (key+1)*resolution, bins[key], float(bins[key])/n*100)

	with open(filename_root + '.' + name + '.autocorr.txt', 'w') as f:
		for v in autocorr:
			print >>f, v

	with open(filename_root + '.' + name + '.stats.txt', 'w') as f:
		print >>f, 'n\t%d' % (n)
		print >>f, 'min\t%d' % (mn)
		print >>f, 'max\t%d' % (mx)
		print >>f, 'mean\t%f' % (mean)
		print >>f, 'stdev\t%f' % (stdev)
