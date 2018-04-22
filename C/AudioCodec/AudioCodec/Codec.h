#ifndef CODEC
#define CODEC

#define FIXED_POINT 32
#include "stdint.h"
#include "kiss_fft\kiss_fftr.h"


const int nfft = 32;

static
kiss_fft_scalar rand_scalar(void)
{
	kiss_fft_scalar s = (kiss_fft_scalar)(rand() - RAND_MAX / 2);
	return s / 2;
}


#endif