CC=gcc
CFLAGS=-I.
TOUCH=touch
RM=rm

all:
	$(TOUCH) credentials.dat
	$(CC) passwd.c -o passwd
	$(CC) passwd2.c -o passwd2
clean:
	$(RM) passwd
	$(RM) passwd2
	$(RM) credentials.dat
