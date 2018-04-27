#ifndef CODEC
#define CODEC

#define FIXED_POINT 32
#include "stdint.h"
#include "kiss_fft\kiss_fftr.h"

#define f_int int32_t
//#define CONV_V 4294967296

//#define f_int int16_t
#define CONV_V 65536

#define SIZE 32640

static
kiss_fft_scalar rand_scalar(void)
{
	kiss_fft_scalar s = (kiss_fft_scalar)(rand() - RAND_MAX / 2);
	return s / 2;
}


#endif