EXE=passwd
CC=gcc
CFLAGS= #Incase you need it

$(EXE): passwd.c main.c passwd.h # You can make it scarrier by using $< and @ (google)
	$(CC) $(CFLAGS) main.o passwd.o -o $(EXE)

passwd.o: passwd.c passwd.h
	#(CC) $(CFLAGS) -c passwd.c

main.o : main.c # this too works

.PHONY:clean

clean: 
	rm -f *.o $(EXE)


