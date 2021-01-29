all: pub sub

pub: pub.o
	gcc pub.o -o pub -lzmq -O3

sub: sub.o
	gcc sub.o -o sub -lzmq -O3

pub.o: pub.c
	gcc -c pub.c

sub.o: sub.c
	gcc -c sub.c

clean:
	$(RM) *.o pub sub
