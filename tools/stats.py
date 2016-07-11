import numpy

def autocorr(x, lag=1):
	if lag == 0: return 1
	return numpy.corrcoef(x[:-lag], x[lag:])[0,1]

def acf(x, nlags):
	return [autocorr(x, i) for i in range(0, nlags)]

