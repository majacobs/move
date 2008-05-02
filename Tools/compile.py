from math import log
#import sys

#if (len(sys.argv) is not 3):
#	print 'Usage: python %s <input filename> <output filename>' % sys.argv[0]
#	sys.exit(0)

def bit_range(num):
	return range(int(log(num)/log(2)), -1, -1)

def build_int(value):
	out = ['wwwawwsd','wwwwwwss','wwwwwawa','wwwawaws']
	for shift in bit_range(value):
		if (value >> shift) & 1:
			out.extend(['wwdwwawa','wawdwwss'])
		else:
			out.append('wwdwwwss')
	return out

def wasd2i(wasd):
	out = 0
	for i in range(0,4):
		out += 4**(3-i) * {'w':0,'a':1,'s':2,'d':3}[wasd[i]]
	return out

def next_free_reg():
	if len(free_registers) == 0:
		return False
	else:
		next = free_registers[0]
		free_registers = free_registers[1:]
		return next

free_registers = range(wasd2i('asww'), wasd2i('dddd'))

#print ''.join(build_int(9820))

#f = open(sys.argv[1], 'r')
f = open('basic_test.txt', 'r')
raw_lines = [x.strip() for x in f.readlines()]
lines = []
f.close()

for l in raw_lines:
	if not (l == '' or l[0] == '#'):
		lines.append(l)