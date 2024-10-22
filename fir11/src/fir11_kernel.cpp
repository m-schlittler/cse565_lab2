/*
        Filename: fir.cpp
                FIR lab wirtten for WES/CSE237C class at UCSD.

        INPUT:
                x: signal (chirp)

        OUTPUT:
                y: filtered output

*/

#include "fir11_kernel.h"

extern "C" {
void fir(data_t *y, data_t x) {
#pragma HLS pipeline II = 1
  coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53};

  // Write your code here
}
}
