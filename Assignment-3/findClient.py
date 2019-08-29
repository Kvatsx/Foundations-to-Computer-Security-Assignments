import mmap
f2 = open('ip.txt', 'r')
f = open('facebook.txt')
s = mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ)
for i in range(190):
	line = f2.readline()
	if s.find(line) == -1:
		print('true')