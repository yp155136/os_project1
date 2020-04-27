CC := gcc
flags := -W -Wall -Wextra -Wshadow -O3

all: scheduler

util.o: util.c util.h
	$(CC) $(flags) util.c -c -o util.o

ds.o: ds.c ds.h
	$(CC) $(flags) ds.c -c -o ds.o

FIFO.o: FIFO.c FIFO.h
	$(CC) $(flags) FIFO.c -c -o FIFO.o

SJF.o: SJF.c SJF.h
	$(CC) $(flags) SJF.c -c -o SJF.o

RR.o: RR.c RR.h
	$(CC) $(flags) RR.c -c -o RR.o

PSJF.o: PSJF.c PSJF.h
	$(CC) $(flags) PSJF.c -c -o PSJF.o

scheduler: scheduler.c scheduler.h util.o ds.o FIFO.o SJF.o RR.o PSJF.o
	$(CC) $(flags) scheduler.c util.o ds.o FIFO.o SJF.o RR.o PSJF.o -o scheduler

clean:
	rm -rf scheduler util.o ds.o FIFO.o SJF.o RR.o PSJF.o

