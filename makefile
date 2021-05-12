CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2

all: primes primes-i steg-decode 

primes: error.o primes.o bitset.o eratosthenes.o
	$(CC) $(CFLAGS) error.o primes.o bitset.o eratosthenes.o -o primes

primes-i: error.o primes-i.o bitset-i.o eratosthenes-i.o
	$(CC) $(CFLAGS) -DUSE_INLINE error.o primes-i.o bitset-i.o eratosthenes-i.o -o primes-i

steg-decode: steg-decode.o ppm.o error.o bitset.o eratosthenes.o
	$(CC) $(CFLAGS) steg-decode.o ppm.o error.o bitset.o eratosthenes.o -o steg-decode

primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o

primes-i.o: primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

ppm.o: ppm.c
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

error.o: error.c
	$(CC) $(CFLAGS) -c error.c -o error.o

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

bitset-i.o: bitset.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

eratosthenes.o: eratosthenes.c
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o 

clean:
	rm *.o primes primes-i steg-decode

run: all
	ulimit -s 65536 && ./primes
	ulimit -s 65536 && ./primes-i

