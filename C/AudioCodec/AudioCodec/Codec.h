#ifndef CODEC
#define CODEC

#define FIXED_POINT 32
#include "stdint.h"
#include "kiss_fft\kiss_fftr.h"


#ifdef FIXED_POINT
#if(FIXED_POINT == 32)
#define datatype int32_t
#else	
#define datatype int16_t
#endif
#else
#define datatype float
#endif

#define SIZE 32640
#define OFFSET 64

static
kiss_fft_scalar rand_scalar(void)
{
	kiss_fft_scalar s = (kiss_fft_scalar)(rand() - RAND_MAX / 2);
	return s / 2;
}


#endif