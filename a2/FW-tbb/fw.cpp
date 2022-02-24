/*
 Standard implementation of the Floyd-Warshall Algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/partitioner.h"

inline int min(int a, int b);

void graph_init_random(int **adjm, int seed, int n,  int m)
{
     unsigned  int i, j;

     srand48(seed);
     for(i=0; i<n; i++)
        for(j=0; j<n; j++)
           adjm[i][j] = abs((( int)lrand48()) % 1048576);

     for(i=0; i<n; i++)adjm[i][i]=0;
}


int main(int argc, char **argv)
{
     int **A;
     struct timeval t1, t2;
     double time;
     int N=1024;
	
     if (argc != 3) {
        fprintf(stdout,"Usage: %s N\n", argv[0]);
        exit(0);
     }

     N=atoi(argv[1]);
 	const int tthreads = atoi(argv[2]);

     A = (int **) malloc(N*sizeof(int *));
     for(int i=0; i<N; i++) A[i] = (int *) malloc(N*sizeof(int));

     graph_init_random(A,-1,N,128*N);

     gettimeofday(&t1,0);
	tbb::task_scheduler_init init(tthreads);
	tbb::affinity_partitioner ap;

     for(int k=0;k<N;k++){
	tbb::parallel_for(
		tbb:: blocked_range<size_t>(0,N,N/tthreads),
		[=]( const tbb::blocked_range<size_t>& r){
			for(size_t i= r.begin(); i!= r.end(); i++)
			   for(int j=0; j<N; j++)
			      A[i][j]=min(A[i][j], A[i][k] + A[k][j]);
		}
		,ap 
	);
     }

     gettimeofday(&t2,0);

     time=(double)((t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec)/1000000;
     printf("FW,%d,%.4f\n", N, time);

     /*
     for(i=0; i<N; i++)
        for(j=0; j<N; j++) fprintf(stdout,"%d\n", A[i][j]);
     */

     return 0;     
}

inline int min(int a, int b)
{
     if(a<=b)return a;
     else return b;
}

