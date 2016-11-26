#ifndef FFTCODE_H
#define FFTCODE_H

#include <iostream>
#include <cstdint>
#include <complex.h>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void fft(CArray& warray);
const double PI = 3.141592653589793;
#endif
