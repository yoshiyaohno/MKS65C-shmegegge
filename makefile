all: shmegegge.o
	gcc shmegegge.o

shmegegge.o: shmegegge.c
	gcc -c shmegegge.c

run:
	./a.out

clean:
	rm a.out *.o
