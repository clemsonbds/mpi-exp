#!/usr/bin/python
import sys

send = []
recv = []

with open(sys.argv[1]) as f:
  for line in f.readlines():
    s, r = line.split()
    send.append(int(s))
    recv.append(int(r))

delay = [recv[i] - send[i] for i in range(0, len(recv))]

jitter = 0
for d in delay:
  jitter += (abs(d) - jitter)/16

print jitter
