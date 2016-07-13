#!/usr/bin/python
import sys

filename = sys.argv[1]
results = {}

with open(filename) as f:
	in_summary = False

	for line in f.readlines():
		if 'Begin' in line or 'End' in line:
			continue

		label, value = line.strip().split("=")

		if label not in results:
			results[label] = []

		results[label].append(value)

num_values = len(results[results.keys()[0]])

#print 'x\t' + '\t'.join(str(i) for i in range(1, num_values+1));

for key in results.keys():
	print key + '\t' + '\t'.join(v for v in results[key])
