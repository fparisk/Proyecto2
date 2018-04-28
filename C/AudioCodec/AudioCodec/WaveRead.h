#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct wav_file {
	unsigned char chunkId[4];
	uint32_t chunkSize;
	unsigned char format[4];
	unsigned char subchunk1Id[4];
	uint32_t subchunk1Size;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
	unsigned char subchunk2Id[4];
	uint32_t subchunk2Size;
	unsigned char * data;
} WavFile;

void swap_endian16(uint16_t val);

void swap_endian32(uint32_t val);
int loadWavFile(const char *filePath, WavFile * wavFile);