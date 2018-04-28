#pragma once
#include "Codec.h"

void EncodeSamples(int size, kiss_fft_scalar rin[], kiss_fft_cpx *cout);