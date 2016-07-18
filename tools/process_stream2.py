#!/usr/bin/env python

import sys
import to_bins
import stats
import numpy
from scipy import stats

filename=sys.argv[1]

send_timestamps = []
recv_timestamps = []
diff_timestamps = []

with open(filename) as f:
	for line in f.readlines():
		send_ts, recv_ts = line.split()
		send_ts = float(send_ts)*1000000
		recv_ts = float(recv_ts)*1000000

		send_timestamps.append(send_ts)
		recv_timestamps.append(recv_ts)
#		diff_timestamps.append(int((recv_ts - send_ts)*1000000))

n = len(send_timestamps)
#gaps = [send_timestamps[i] - send_timestamps[i-1] for i in range(1, n)]

#subsets = 50
#for i in range(subsets):
#	subset = gaps[i*n/subsets:(i+1)*n/subsets]
#	print numpy.mean(subset), numpy.std(subset)
#exit()

#gap_mean = (send_timestamps[-1] - send_timestamps[0]) / (n-1)
#send_lateness = [send_timestamps[i] - send_timestamps[0] - gap_mean * i for i in range(n)]

#gap_mean = (recv_timestamps[-1] - recv_timestamps[0]) / (n-1)
#recv_lateness = [recv_timestamps[i] - recv_timestamps[0] - gap_mean * i for i in range(n)]

#for x in send_lateness:
#	print x
#exit()

diff_timestamps = [recv_timestamps[i] - send_timestamps[i] for i in range(n)]

diff_min = numpy.min(diff_timestamps)

#zero_diff_timestamps = [x - diff_min for x in diff_timestamps]

#print stats.linregress(range(n), diff_timestamps)
#exit()
slope, intercept, _, _, _ = stats.linregress(range(n), diff_timestamps)
#print slope, intercept

corrected = [diff_timestamps[i] - (slope * i + intercept) for i in range(n)]

diff_min = numpy.min(corrected)

skewed = [x - diff_min for x in corrected]

#print numpy.max(skewed), numpy.min(skewed), numpy.mean(skewed), numpy.std(skewed)
for x in skewed:
	print x

#for x in diff_timestamps:
#	print x - diff_min
#	print x
