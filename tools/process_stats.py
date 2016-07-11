#!/usr/bin/python

if __name__ == "__main__":
	import sys
	filename = sys.argv[1]
	nlags = int(sys.argv[2])

	arr = []

	with open(filename) as f:
		for line in f.readlines():
			arr.append(int(line))

	import stats
	ac = stats.acf(arr, nlags)

	for x in ac:
		print x
