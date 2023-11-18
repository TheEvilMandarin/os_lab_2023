CC=gcc
CFLAGS=-I.

TARGETS=parallel_min_max zombie process_memory parallel_sum

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -g -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

zombie :
	$(CC) -o zombie zombie.c $(CFLAGS)

process_memory :
	$(CC) -o process_memory process_memory.c $(CFLAGS)

parallel_sum : utils.o sum.o utils.h sum.h parallel_sum.c
	$(CC) -g -o parallel_sum utils.o sum.o parallel_sum.c $(CFLAGS)

sum.o : sum.h sum.c
	$(CC) -g -o sum.o -c sum.c $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_min_maxtest.txt

all: $(TARGETS)