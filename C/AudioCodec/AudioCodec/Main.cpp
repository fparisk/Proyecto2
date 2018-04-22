#include "Decoder.h"
#include "Encoder.h"
#include "WaveWrite.h"
#include <stdlib.h>

// -------------------------------------------------------- [ Section: Main ] -
void CreateWave(float *samples) 
{
	// Define some variables for the sound
	float sampleRate = 44100.0; // hertz
	float freq = 440.0;         // hertz
	float duration = 1;       // seconds

	//int nSamples = (int)(duration*sampleRate);
	int nSamples = 32000;
	duration = (float)nSamples / sampleRate;

	// Create a mono (1), 32-bit sound and set the duration
	Wave mySound = makeWave((int)sampleRate, 1, 32);
	waveSetDuration(&mySound, duration);

	// Add all of the data
	int i;
	float frameData[1];
	//memcpy(frameData,samples,nfft);
	int index = 0;
	for (i = 0; i<nSamples; i += 1) {
		//frameData[0] = cos(freq*(float)i*3.14159 / sampleRate);
		frameData[0] = samples[i];
		waveAddSample(&mySound, frameData);
		/*index++;
		if (index >= nfft)
		{
			index = 0;
		}*/
	}

	// Write it to a file and clean up when done
	waveToFile(&mySound, "pmono-32bit.wav");
	waveDestroy(&mySound);
}


void TestSamples(int16_t samples[])
{
	int16_t data[nfft] = { 50, 60, 70, 79, 86, 92, 97, 99, 100, 98, 95, 90, 83, 74, 65,
						 55, 45, 35, 26, 17, 10, 5, 2, 0, 1, 3, 8, 14, 21, 30, 40, 50 };
	samples = data;
}

float Convert(int32_t value)
{
	float fvalue = (float)value / 65536;
	return fvalue;
}

const char* getData(char* line)
{
	const char* tok;
	for (tok = strtok(line, "\n");
		tok && *tok;
		tok = strtok(NULL, ";\n"))
	{
			return tok;
	}
	return NULL;
}

int main()
{
	//int16_t *samples = static_cast<int16_t *>(malloc(nfft * sizeof(*samples)));
	//int16_t *samples = (int16_t*)malloc(nfft * (sizeof(int16_t)));
	int16_t samples[nfft] = { 50, 60, 70, 79, 86, 92, 97, 99, 100, 98, 95, 90, 83, 74, 65,
		55, 45, 35, 26, 17, 10, 5, 2, 0, 1, 3, 8, 14, 21, 30, 40, 50 };

	FILE* stream = fopen("stest.csv", "r");

	int32_t tsamps[32640];

	int ti = 0;
	char line[1024];
	while (fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		tsamps[ti] = atoi(getData(tmp));
		ti++;
		free(tmp);
	}

	kiss_fft_scalar rin[nfft];
	kiss_fft_cpx sout[nfft];
	kiss_fft_scalar rout[nfft];

	//TestSamples(samples);

	for(int i = 0; i<nfft; ++i) 
	{
		rin[i] = samples[i];
	}

	EncodeSamples(nfft, rin, sout);
	DecodeSamples(nfft, sout, rout);

	float fsamples[nfft];
	for (int i = 0; i<nfft; ++i) 
	{
		fsamples[i] = Convert(rout[i]);
	}

	CreateWave(fsamples);

	return 0;
}



