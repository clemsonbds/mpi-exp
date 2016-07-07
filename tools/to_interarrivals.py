#!/usr/bin/python

def to_interarrivals(times):
	return [times[i] - times[i-1] for i in range(1, len(times))]
	
if __name__ == "__main__":
	import sys
	with open(sys.argv[1]) as f:
		times = []
		interarrivals = []

		for line in f.readlines():
			fields = line.split()
			if len(fields) == 0:
				break
			hour, min, sec = fields[0].split(":")
			ts_sec = int(hour)*3600 + int(min)*60 + float(sec)
			times.append(ts_sec)

		for t in to_interarrivals(times):
			print t
