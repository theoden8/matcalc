#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

typedef int int_t;

__device__ int_t x;

#define THREADS_PER_BLOCK 512
__global__ void kernel(int_t N) {
	const int_t
		T = blockIdx.x * THREADS_PER_BLOCK + threadIdx.x + 2;
	int_t a = N, b = T;
	/* printf("DEVICE [%d]: CALLED FOR (%d)\n", T, N); */
	if(T > N)
		return;
	/* printf("DEVICE [%d]: STARTED WITH VALUE (%d)\n", b, x); */
	while(a > 0 && b > 0) {
		if(a == 1 || b == 1) {
			/* printf("DEVICE: INCR\n"); */
			atomicAdd(&x, 1);
			return;
			/* goto end; */
		} else if(a > b) {
			a -= a / b * b;
		} else if(a < b) {
			b -= b / a * a;
		} else {
			if(a == 1) {
				/* printf("DEVICE: INCR\n"); */
				atomicAdd(&x, 1);
			}
			return;
			/* goto end; */
		}
	}
	if(a == 1 || b == 1) {
		/* printf("DEVICE: INCR\n"); */
		atomicAdd(&x, 1);
	}
/* end: */
/* 	; */
	/* printf("DEVICE: (%d, %d) FINISHED WITH RESULT %d\n", T, N, x); */
	/* __syncthreads(); */
	/* if(T + 1 == N) { */
	/* 	printf("%d\n", x); */
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
	if(argc != 2) {
		fputs("argc != 2", stderr);
		return EXIT_FAILURE;
	}

	const int_t N = atol(argv[1]);
	if(N < 1) {
		fputs("invalid domain", stderr);
		return EXIT_FAILURE;
	}

	int_t x_copy;
	static const int_t x_default = 1;
	if(N >= 1)
		puts("1");
	for(int_t i = 2; i <= N; ++i) {
		cudaMemcpyToSymbol(x, &x_default, sizeof(int_t));
		CUDACHK;
		const int no_threads = i - 2;
		const int no_blocks = no_threads / THREADS_PER_BLOCK;
		kernel<<<no_blocks + 1, THREADS_PER_BLOCK>>>(i);
		CUDACHK;
		cudaMemcpyFromSymbol(&x_copy, x, sizeof(int_t), 0, cudaMemcpyDeviceToHost);
		CUDACHK;
		printf("%d\n", x_copy);
	}
}
