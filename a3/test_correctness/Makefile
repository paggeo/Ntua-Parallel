CC=mpicc
CFLAGS=-O3 -lm -Wall
RES=-DPRINT_RESULTS
CONV=-DTEST_CONV

all: jacobi seidelsor redblacksor 

jacobi: Jacobi_mpi.c utils.c
	$(CC) $(CFLAGS) $(RES) Jacobi_mpi.c utils.c -o jacobi

seidelsor: GaussSeidelSOR_mpi.c utils.c
	$(CC) $(CFLAGS) $(RES) GaussSeidelSOR_mpi.c utils.c -o seidelsor

redblacksor: RedBlackSOR_mpi.c utils.c
	$(CC) $(CFLAGS) $(RES) RedBlackSOR_mpi.c utils.c -o redblacksor

clean:
	rm jacobi seidelsor redblacksor res*
