#include "Encoder.h"

void EncodeSamples(int size, kiss_fft_scalar rin[], kiss_fft_cpx *cout)
{
	//kiss_fft_cpx sout[nfft];
	kiss_fftr_cfg  kiss_fftr_state;
	//kiss_fft_scalar rin[nfft + 2];

	kiss_fftr_state = kiss_fftr_alloc(size, 0, 0, 0);
	
	kiss_fftr(kiss_fftr_state, rin, cout);

	free(kiss_fftr_state);

}