al = "(tcp.port==443) and not (ip.addr=="
for i in range(15):
	text = input().split("\t")
	# print(text)
	al = al + text[0] +" or ip.addr=="
print(al)