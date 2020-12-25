#define N 11
#include "ap_int.h"


typedef int coef_t;
typedef int data_t;
typedef int acc_t;
typedef int int32_t;

void fir(volatile int32_t* y, volatile int32_t* x) {
	coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53};
	static int32_t shift_reg[N];
	acc_t acc;
	int i;
	int j;


TOP_LOOP:
	for (j=0; j<256; j++){
	acc = 0;

Shift_Accum_Loop:
	for (i = N - 1; i >= 0; i--) {
		if (i == 0) {
			acc += x[j] * c[0];
			shift_reg[0] = x[j];
		} else {
			shift_reg[i] = shift_reg[i - 1];
			acc += shift_reg[i] * c[i];
		}
	}


/*
Shift_Accum_Loop:
	for (i = N - 1; i > 0; i--) {
		shift_reg[i] = shift_reg[i - 1];
		acc += shift_reg[i] * c[i];
	}

	acc += x * c[0];
	shift_reg[0] = x;
*/
/*
TDL:
	for (i = N - 1; i > 0; i--) {
		shift_reg[i] = shift_reg[i - 1];
	}
	shift_reg[0] = x[j];

	acc = 0;
	MAC:
	for (i = N - 1; i >= 0; i--) {
		acc += shift_reg[i] * c[i];
	}
*/

	y[j]= acc;

    }
	return;
}


