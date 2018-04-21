#include "Decoder.h"
#include "Encoder.h"


int main()
{
	kiss_fft_scalar rin[nfft + 2];
	kiss_fft_cpx sout[nfft];
	kiss_fft_scalar rout[nfft + 2];

	for(int i = 0; i<nfft; ++i) {
		rin[i] = rand_scalar();
	}

	EncodeSamples(nfft, rin, sout);
	DecodeSamples(nfft, sout, rout);
	return 0;
}

