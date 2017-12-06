#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

typedef int int_t;

__device__ int_t x;

// eulers totient funtion (commonly abbreviated as phi, here: etf)
// etf(1) = 1
// etf(n) = reduce (+) (map (coprime n) [1..n])
//
// the way to calculate it here is to use the amazing gpu cores for euclidean
// algorithm.

#define THREADS_PER_BLOCK 512
__device__ int_t coprime(int_t a, int_t b) {
	while(a > 0 && b > 0) {
		if(a == 1 || b == 1) {
			return 1;
		} else if(a > b) {
			a -= a / b * b;
		} else if(a < b) {
			b -= b / a * a;
		} else {
			if(a == 1)
				return 1;
			return 0;
		}
	}
	if(a == 1 || b == 1) {
		return 1;
	}
	return 0;
}

__global__ void kernel(int_t N) {
	__shared__ int_t mem[THREADS_PER_BLOCK];
	int tid = threadIdx.x;
	const int_t T = blockIdx.x * THREADS_PER_BLOCK + threadIdx.x + 2;
	if(T > N)
		return;
	mem[tid] = coprime(N, T);
	__syncthreads();
	for(unsigned int s = blockDim.x >> 1; s > 0; s >>= 1) {
		if(tid < s) {
			mem[tid] += mem[tid + s];
		}
		__syncthreads();
	}
	/* if(tid == 0) { */
	/* 	atomicAdd(&x, mem[0]); */
	/* } */
}

#ifdef NDEBUG
#define CUDACHK if(cuda_check() != EXIT_SUCCESS) return EXIT_FAILURE;
int cuda_check() {
	cudaError_t err = cudaGetLastError();
	if(err != cudaSuccess)  {
		fprintf(stderr, "error: %s\n", cudaGetErrorString(err));
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
#else
#define CUDACHK
#endif

int main(int argc, char *argv[]) {
	if(argc != 2 && argc != 3) {
		fputs("error: invalid number of arguments", stderr);
		return EXIT_FAILURE;
	}

	bool ranged = argc == 3;
	const int_t S = ranged ? atol(argv[1]) : 1;
	const int_t N = atol(argv[ranged ? 2 : 1]);
	if(S < 1 || N < S) {
		fputs("invalid domain", stderr);
		return EXIT_FAILURE;
	}

	int_t x_copy;
	static const int_t x_default = 1;
	if(S <= 1 && N >= 1)
		puts("1");
	for(int_t i = S + 1; i <= N; ++i) {
		cudaMemcpy(x, &x_default, sizeof(int_t), cudaMemcpyHostToDevice);
		CUDACHK;
		const int no_threads = i - 2;
		const int no_blocks = no_threads / THREADS_PER_BLOCK;
		kernel<<<no_blocks + 1, THREADS_PER_BLOCK>>>(i);
		CUDACHK;
		cudaMemcpy(&x_copy, x, sizeof(int_t), cudaMemcpyDeviceToHost);
		CUDACHK;
		printf("%d\n", x_copy);
	}
}
