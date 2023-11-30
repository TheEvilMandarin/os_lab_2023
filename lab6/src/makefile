CC=gcc
CFLAGS=-I.
CURRENT_DIR=$(notdir $(patsubst %/,%,$(dir $(mkfile_path))))


multmodulo.so : multmodulo.h 
	$(CC) -c -fPIC multmodulo.c -o multmodulo.o
	$(CC) -o multmodulo.so -shared multmodulo.o

server: multmodulo.so
	$(CC) -c server.c -o server.o
	$(CC) -o server server.o -L$(shell pwd) -lFact -pthread -Wl,-rpath=$(shell pwd) $(CFLAGS)

client: multmodulo.so
	$(CC) -c client.c -o client.o
	$(CC) -o client client.o -L$(shell pwd) -lFact -pthread -Wl,-rpath=$(shell pwd) $(CFLAGS)

all: multmodulo.so client server

clean:
	rm client client.o server server.o multmodulo.o multmodulo.so