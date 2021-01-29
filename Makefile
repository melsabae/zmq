GIT_VERSION = $(shell git describe --all)
GIT_HASH = $(shell git hist -1 | cut -f2 -d' ')
CFLAGS = -O3 -DGIT_VERSION=\"$(GIT_VERSION)\" -DGIT_HASH=\"$(GIT_HASH)\"

all: objects
	gcc proxy.o -o proxy -lzmq $(CFLAGS)
	gcc sub.o -o sub -lzmq $(CFLAGS)
	gcc pub.o -o pub -lzmq $(CFLAGS)

objects:
	gcc -c *.c -lzmq -O3 $(CFLAGS)

clean:
	$(RM) *.o proxy sub pub
