import sys

if (len(sys.argv) is not 3):
	print "Usage: python %s <input filename> <output filename>" % sys.argv[0]
	sys.exit(0)

f = open(sys.argv[1], 'r')
raw_lines = [x.strip() for x in f.readlines()]
lines = []
f.close()

defines = {}
commands = []

def swap_em(x):
	if x in defines:
		return defines[x]
	else:
		return x

for l in raw_lines:
	if not (l == '' or l[0] == '-'):
		lines.append(l)

backward = False
try:
	div = lines.index('%%')
	for d in lines[0:div]:
		if d == '<-':
			backward = True
		else:
			bits = d.split()
			defines[bits[0]] = bits[1]
	code = lines[div+1:]
except:
	code = lines

for c in code:
	commands.extend(c.split())

commands = map(swap_em, commands)

if backward:
	out = ''
	temp = ''
	for i in range(0,len(commands)):
		if i % 2 == 0:
			temp = commands[i]
		else:
			out += commands[i] + temp
	if len(commands) % 2 == 0:
		out += temp
else:
	out = ''.join(commands)

compiled = open(sys.argv[2], 'w')
compiled.write(out)
compiled.close()