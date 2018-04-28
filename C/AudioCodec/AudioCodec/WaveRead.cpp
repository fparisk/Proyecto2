#include "WaveRead.h"

void swap_endian16(uint16_t val) {
	val = (val << 8) | (val >> 8);
}

void swap_endian32(uint32_t val) {
	val = (val << 24) | ((val << 8) & 0x00ff0000) |
		((val >> 8) & 0x0000ff00) | (val >> 24);
}

int loadWavFile(const char *filePath, WavFile * wavFile) {
	int rc = 0;
	FILE *fp = fopen(filePath, "rb");
	printf("wavreader file Path = %s from %s", (fp ? "file opened" : "failed to open file"), filePath);
	if (!fp) {
		rc = -2;//CANNOT_OPEN_FILE_ERROR;
		return rc;
	}

	//chunkId
	size_t len = fread(wavFile->chunkId, sizeof(unsigned char), 4, fp);
	wavFile->chunkId[len] = '\0';
	printf("wavreader len:%d chunkId: %s", (int)len, wavFile->chunkId);
	if (strcmp((const char *)wavFile->chunkId, "RIFF")) {
		rc = -3;//NOT_WAV_FILE_ERROR;
		return rc;
	}

	//chunkSize
	fread(&wavFile->chunkSize, sizeof(uint32_t), 1, fp);
	swap_endian32(wavFile->chunkSize);
	printf("wavreader chunkSize: %d", wavFile->chunkSize);

	//format
	len = fread(wavFile->format, sizeof(unsigned char), 4, fp);
	wavFile->format[len] = '\0';
	printf("wavreader format: %s", wavFile->format);
	if (strcmp((const char *)wavFile->format, "WAVE")) {
		rc = -4;//FMT_ERROR;
		return rc;
	}

	//subchunk1Id
	len = fread(wavFile->subchunk1Id, sizeof(unsigned char), 4, fp);
	wavFile->subchunk1Id[len] = '\0';
	printf("wavreader subchunk1Id: %s", wavFile->subchunk1Id);
	if (strcmp((const char *)wavFile->subchunk1Id, "fmt ")) {
		rc = -5;//FMT_ID_ERROR;
		return rc;
	}

	//subchunk1Size
	fread(&wavFile->subchunk1Size, sizeof(uint32_t), 1, fp);
	swap_endian32(wavFile->subchunk1Size);
	printf("wavreader subchunk1Size: %d", wavFile->subchunk1Size);

	//audioFormat
	fread(&wavFile->audioFormat, sizeof(uint16_t), 1, fp);
	swap_endian16(wavFile->audioFormat);
	printf("wavreader audioFormat: %d", wavFile->audioFormat);

	//numChannels
	fread(&wavFile->numChannels, sizeof(uint16_t), 1, fp);
	swap_endian16(wavFile->numChannels);
	printf("wavreader numChannels: %d", wavFile->numChannels);

	//sampleRate
	fread(&wavFile->sampleRate, sizeof(uint32_t), 1, fp);
	swap_endian32(wavFile->sampleRate);
	printf("wavreader sampleRate: %d", wavFile->sampleRate);

	//byteRate
	fread(&wavFile->byteRate, sizeof(uint32_t), 1, fp);
	swap_endian32(wavFile->byteRate);
	printf("wavreader byteRate: %d", wavFile->byteRate);

	//blockAlign
	fread(&wavFile->blockAlign, sizeof(uint16_t), 1, fp);
	swap_endian16(wavFile->blockAlign);
	printf("wavreader blockAlign: %d", wavFile->blockAlign);

	//bitsPerSample
	fread(&wavFile->bitsPerSample, sizeof(uint16_t), 1, fp);
	swap_endian16(wavFile->blockAlign);
	printf("wavreader bitRate: %d", wavFile->blockAlign);

	//subchunk2Id
	fread(wavFile->subchunk2Id, sizeof(unsigned char), 4, fp);
	wavFile->subchunk2Id[len] = '\0';
	printf("wavreader subchunk2Id: %s", wavFile->subchunk2Id);

	fread(&wavFile->subchunk2Size, sizeof(uint32_t), 1, fp);
	swap_endian32(wavFile->subchunk2Size);
	printf("wavreader subchunk2Size: %d", wavFile->subchunk2Size);

	wavFile->data = (unsigned char *)malloc(sizeof(unsigned char) * wavFile->subchunk2Size); //set aside sound buffer space
	fread(wavFile->data, sizeof(unsigned char), wavFile->subchunk2Size, fp); //read in our whole sound data chunk
	fclose(fp);
	return rc;
}