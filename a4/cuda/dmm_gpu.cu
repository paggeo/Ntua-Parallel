/*
 *  dmm_gpu.cu -- Template for DMM GPU kernels
 *
 *  Copyright (C) 2020, Computing Systems Laboratory (CSLab)
 *  Copyright (C) 2020, Athena Elafrou/Petros Anastasiadis
 */
#include "dmm.h"
#include "stdio.h"
#include <cublas_v2.h>

/*
 *  Naive kernel
 */
__global__ void dmm_gpu_naive(const value_t *A, const value_t *B, value_t *C,
		const size_t M, const size_t N, const size_t K) {

	/* Compute the row and the column of the current thread */

	int bx = blockIdx.x;
	int by = blockIdx.y;
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	int row = by*blockDim.y + ty;
	int col = bx*blockDim.x + tx;

	value_t dot = 0;

	/* If the thread's position is out of the array, it remains inactive */
	while (row < M && col < N){
		/* Compute the value of C */
		for (int k = 0; k < K; k++){
			dot += A[row*K+k]*B[col+k*N];
		}
		C[row*N+col]=dot;
		row += blockDim.y*gridDim.y;
		col += blockDim.x*gridDim.x;
	}

}

/*
 *  Coalesced memory acceses of A.
 */
__global__ void dmm_gpu_coalesced_A(const value_t *A, const value_t *B,
		value_t *C, const size_t M, const size_t N,
		const size_t K) {

	/* Define the shared memory between the threads of the same thread block */
	__shared__ value_t A_shared[TILE_Y*TILE_X];

	int bx = blockIdx.x;
	int by = blockIdx.y;
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	/* Compute the tile of the current thread */
	int row = by * TILE_Y + ty;
	int col = bx * TILE_X + tx;

	value_t dot = 0;

	for(int m = 0; m < K; m+=TILE_X){
		/* Load the current tile in the shared memory and synchronize */
		A_shared[ty*TILE_X+tx] = A[row*K + m+tx];

		__syncthreads();

		for(int k = 0; k < TILE_X; k++){
			/* Compute the inner product of current tile and synchronize */
			// This has to be A goes from tile to tile 
			// But B traverse the hole block so is the same with 
			// the naive but you have to change from B[k*N + col]
			// to B[(m+k)*N+col] because here k is only in the tile
			dot += A_shared[ty*TILE_X+k]*B[(m+k)*N+col];
		}
		__syncthreads();
	}
	/* Save result */
	C[row*N+col] = dot;

}

/*
 *  Reduced memory accesses.
 */
__global__ void dmm_gpu_reduced_global(const value_t *A, const value_t *B, value_t *C,
		const size_t M, const size_t N, const size_t K) {

	/* Define the shared memory between the threads of the same thread block */
	__shared__ value_t A_shared[TILE_Y*TILE_X];
	__shared__ value_t B_shared[TILE_Y*TILE_X];

	int bx = blockIdx.x;
	int by = blockIdx.y;
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	int row = by * TILE_Y + ty;
	int col = bx * TILE_X + tx;

	value_t dot = 0;

	for(int m = 0; m < K; m+=TILE_X){
		A_shared[ty*TILE_X+tx] = A[row*K + m+tx];
		// If TILE.x != TILE.y we have to do this differently
		// I dont think this can happen because we add more 
		// complexity than nessesary. Either way every element will  
		// be excecuted in 32 wraps so no need for extra thinking.
		B_shared[ty*TILE_X+tx] = B[col + (m+ty)*N];
		
		__syncthreads();

		for(int k = 0; k < TILE_X; k++){
			dot += A_shared[ty*TILE_X+k]*B_shared[k*TILE_X+tx];
		}
		__syncthreads();
	}
	C[row*N+col] = dot;

}

/*
 *  Use of cuBLAS
 */
// C(m,n) = A(m,k) * B(k,n)
void dmm_gpu_cublas(const value_t *A, const value_t *B, value_t *C,
		const size_t M, const size_t N, const size_t K) {

	/* Define parameters for cublasSgemm */

	int lda = N;
	int ldb = K;
	int ldc = N;
	
	const float alph = 1;
	const float bet = 0;
	const float *alpha = &alph;
	const float *beta = &bet;
	
	/* Create a handle for CUBLAS */
	cublasHandle_t handle;
	cublasCreate(&handle);

	/* Compute the matrix multiplication */
	cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, M, K, alpha, A, lda, B, ldb, beta, C, ldc);

	/* Destroy the handle */
	cublasDestroy(handle);
}
