
#include "stdio.h"
//#include <hls_stream.h>

typedef int coef_t;
typedef int data_t;
typedef int acc_t;
typedef int int32_t;
//typedef hls::stream<data_t> stream_t;

#define NUM_TAPS 11
void fir(volatile int32_t* y, volatile int32_t* x);

const int SIZE = 256;

int main() {
	int32_t x[SIZE], out[SIZE];
	int i = 0;

	for (i=0 ; i < SIZE; i++) {
		printf("%d \n",i);
		x[i] = i;
	}

	fir(out, x);

	if (out[255] == 262500) {
		printf("Result: %d \n", out[255]);
		return 0;
	} else {
		return 1;
	}
}
