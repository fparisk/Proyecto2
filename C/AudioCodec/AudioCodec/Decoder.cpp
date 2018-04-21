#include "Decoder.h"

void DecodeSamples(int size, kiss_fft_cpx cin[], kiss_fft_scalar *rout)
{

	//kiss_fft_cpx cin[nfft];
	kiss_fftr_cfg  kiss_fftr_state;

	// conjugate symmetry of real signal 
	for (int i = 1; i< size / 2; ++i) {
		cin[size - i].r = cin[i].r;
		cin[size - i].i = -cin[i].i;
	}


	//kiss_fft_scalar rout[nfft + 2];

	kiss_fftr_state = kiss_fftr_alloc(size, 1, 0, 0);

	kiss_fftri(kiss_fftr_state, cin, rout);

	free(kiss_fftr_state);

}