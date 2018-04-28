#include "Decoder.h"
#include "Encoder.h"
#include "WaveWrite.h"
#include "FileUtilities.h"
#include "WaveRead.h"
#include <stdlib.h>

// -------------------------------------------------------- [ Section: Main ] -
void CreateWave(float *samples) 
{
	// Define some variables for the sound
	float sampleRate = 8000.0; // hertz
	//float freq = 440.0;         // hertz
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


void TestSamples(datatype samples[])
{
	datatype data[32] = { 50, 60, 70, 79, 86, 92, 97, 99, 100, 98, 95, 90, 83, 74, 65,
						 55, 45, 35, 26, 17, 10, 5, 2, 0, 1, 3, 8, 14, 21, 30, 40, 50 };
	samples = data;
}

float Convert(datatype value)
{
	
	float fvalue = (float)value;
#ifdef FIXED_POINT
	fvalue = fvalue/SIZE - OFFSET;
#endif
	return fvalue;
}

float ConvertComplex(datatype value)
{
	float fvalue = (float)value;
#ifdef FIXED_POINT
	fvalue = fvalue/ 65536;
#endif
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

	//const int SIZE = 32640;
	datatype samples[32] = { 50, 60, 70, 79, 86, 92, 97, 99, 100, 98, 95, 90, 83, 74, 65,
		55, 45, 35, 26, 17, 10, 5, 2, 0, 1, 3, 8, 14, 21, 30, 40, 50 };

	WavFile *myWav = (WavFile*)malloc(sizeof(WavFile));
	loadWavFile("muestra.wav",myWav);

	int *data = (int *)malloc(sizeof(int)*(myWav->subchunk2Size));
	for (int i = 0; i < myWav->subchunk2Size; i++)
	{
		data[i] = myWav->data[i];
	}

	FILE* stream = fopen("matlabSamples.csv", "r");

	int16_t tsamps[SIZE];

	int ti = 0;
	char line[1024];
	while (fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		tsamps[ti] = atoi(getData(tmp));
		ti++;
		free(tmp);
	}

	//float ttsamples[SIZE];

	float fsamples[SIZE];
	float isamples[SIZE];

	kiss_fft_scalar rin[SIZE];
	kiss_fft_cpx sout[SIZE];
	kiss_fft_scalar rout[SIZE];

	//TestSamples(samples);
	
	int sum  = 0;
	for(int i = 0; i<SIZE; ++i)
	{
		rin[i] = tsamps[i];
		//rin[i] = data[i*4];
		//insamples[i] = (float)(data[i]);
		fsamples[i] = (float)rin[i];
		sum += tsamps[i];
	}

	WriteSingleColumn(SIZE, fsamples, "readSamples.csv");

	EncodeSamples(SIZE, rin, sout);
	DecodeSamples(SIZE, sout, rout);

	
	for (int i = 0; i<SIZE; ++i)
	{
		fsamples[i] = ConvertComplex(sout[i].r);
		isamples[i] = ConvertComplex(sout[i].i);
	}

	WriteDualColumn(SIZE, fsamples,isamples, "fftSamples.csv");


	for (int i = 0; i<SIZE; ++i)
	{
		fsamples[i] = Convert(rout[i]);
	}

	//float isamples[SIZE];
	//for (int i = 0; i<SIZE; ++i)
	//{
	//	isamples[i] = Convert(sout[i].i);
	//}

	//WriteFile(SIZE, isamples, "itest.csv");

	//for (int i = 0; i<SIZE; ++i)
	//{
	//	isamples[i] = Convert(sout[i].r);
	//}

	//WriteFile(SIZE, isamples, "rtest.csv");

	WriteSingleColumn(SIZE, fsamples, "OutSamples.csv");
	CreateWave(fsamples);

	return 0;
}



