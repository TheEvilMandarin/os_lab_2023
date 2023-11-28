CC=gcc
CFLAGS=-I.
LDFLAGS=-lpthread

TARGETS=mutex factorial deadlock

mutex :
	$(CC) $(CFLAGS) -o mutex mutex.c $(LDFLAGS)

factorial :
	$(CC) $(CFLAGS) -o factorial factorial.c $(LDFLAGS)

deadlock :
	$(CC) $(CFLAGS) -o deadlock deadlock.c $(LDFLAGS)

clean :
	rm mutex factorial deadlock

all: $(TARGETS)