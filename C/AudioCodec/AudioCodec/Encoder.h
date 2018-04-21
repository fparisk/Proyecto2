#pragma once

#include "kiss_fft\kiss_fftr.h"
#include "Codec.h"

void EncodeSamples(int size, kiss_fft_scalar rin[], kiss_fft_cpx *cout);