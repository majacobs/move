import sys

if (len(sys.argv) is not 2):
	print "Usage: python compile.py <filename>"
	sys.exit(0)

f = open(sys.argv[1], 'r')
lines = f.readlines()

for line in lines:
	if line.startswith('-'):
		lines.remove(line)

for line in lines:
	print line