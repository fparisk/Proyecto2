#pragma once
#include "kiss_fft\kiss_fftr.h"
#include "Codec.h"

void DecodeSamples(int size, kiss_fft_cpx cin[], kiss_fft_scalar *rout);
