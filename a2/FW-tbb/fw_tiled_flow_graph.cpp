/*
   Tiled version of the Floyd-Warshall algorithm.
   command-line arguments: N, B
   N = size of graph
   B = size of tile
   works only when N is a multiple of B
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "tbb/flow_graph.h"
#include "tbb/task_scheduler_init.h"

using namespace tbb::flow;

inline int min(int a, int b);
inline void FW(int **A, int K, int I, int J, int N);

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
	int i,j,k;
	struct timeval t1, t2;
	double time;
	int B=64;
	int N=1024;

	if (argc != 4){
		fprintf(stdout, "Usage %s N B\n", argv[0]);
		exit(0);
	}

	N=atoi(argv[1]);
	B=atoi(argv[2]);
	const int tthreads = atoi(argv[3]);

	A=(int **)malloc(N*sizeof(int *));
	for(i=0; i<N; i++)A[i]=(int *)malloc(N*sizeof(int));

	graph_init_random(A,-1,N,128*N);

	tbb::task_scheduler_init init(tthreads);
	gettimeofday(&t1,0);

	for(k=0;k<N;k+=B){
		graph g;
		broadcast_node< continue_msg > start(g);	
		continue_node <continue_msg> Akk(g , [&] ( const continue_msg &) {FW(A,k,k,k,B);});
		
		continue_node <continue_msg> Aik(g , [&] ( const continue_msg &) {for(int i=0; i<k; i+=B) FW(A,k,i,k,B);});
		continue_node <continue_msg> Aki(g , [&] ( const continue_msg &) {for(int i=k+B; i<N; i+=B) FW(A,k,i,k,B);});
		continue_node <continue_msg> Ajk(g , [&] ( const continue_msg &) {for(int j=0; j<k; j+=B) FW(A,k,k,j,B);});
		continue_node <continue_msg> Akj(g , [&] ( const continue_msg &) {for(int j=k+B; j<N; j+=B) FW(A,k,k,j,B);});

		continue_node <continue_msg> Aij1(g , [&] ( const continue_msg &) {for(int i=0; i<k; i+=B) for(int j=0; j<k; j+=B) FW(A,k,i,j,B);});
		continue_node <continue_msg> Aij2(g , [&] ( const continue_msg &) {for(int i=0; i<k; i+=B) for(int j=k+B; j<N; j+=B) FW(A,k,i,j,B);});
		continue_node <continue_msg> Aij3(g , [&] ( const continue_msg &) {for(int i=k+B; i<N; i+=B) for(int j=0; j<k; j+=B) FW(A,k,i,j,B);});
		continue_node <continue_msg> Aij4(g , [&] ( const continue_msg &) {for(int i=k+B; i<N; i+=B) for(int j=k+B; j<N; j+=B) FW(A,k,i,j,B);});
		
		make_edge(start,Akk);	
		make_edge(Akk,Aik);
		make_edge(Akk,Aki);
		make_edge(Akk,Ajk);
		make_edge(Akk,Akj);
		make_edge(Aik,Aij1);
		make_edge(Ajk,Aij1);
		make_edge(Aik,Aij2);
		make_edge(Akj, Aij2);
		make_edge(Aki, Aij3);
		make_edge(Ajk, Aij3);
		make_edge(Aki, Aij4);
		make_edge(Akj, Aij4);
		
		
		Akk.try_put(continue_msg());
                g.wait_for_all();
	}
	gettimeofday(&t2,0);

	time=(double)((t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec)/1000000;
	printf("FW_TILED_FLOW_GRAPH,%d,%d,%.4f\n", N,B,time);

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

inline void FW(int **A, int K, int I, int J, int N)
{
	int i,j,k;

	for(k=K; k<K+N; k++)
		for(i=I; i<I+N; i++)
			for(j=J; j<J+N; j++)
				A[i][j]=min(A[i][j], A[i][k]+A[k][j]);

}
