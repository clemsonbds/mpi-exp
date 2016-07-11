#!/usr/bin/python

import sys

times = []

for i in range(1, len(sys.argv)):
  with open(sys.argv[i]) as f:
    for line in f.readlines():
      times.append(int(float(line)*1000000))

import numpy
print numpy.mean(times), numpy.std(times)
