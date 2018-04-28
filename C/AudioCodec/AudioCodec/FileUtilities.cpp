#include "FileUtilities.h" 

int WriteSingleColumn(int count, float *data, char const *fileName)
{
	FILE *f = fopen(fileName, "w");
	if (f == NULL) return -1;
	//while (count-- > 0) 
	//{
	//	// you might want to check for out-of-disk-space here, too 
	//	fprintf(f, "%f\n", &data);
	//	++data;
	//}
	for (int i = 0; i < count; ++i)
	{
		fprintf(f, "%f\n", data[i]);
	}

	fclose(f);
	return 0;
}

int WriteDualColumn(int count, float *data1, float *data2, char const *fileName)
{
	FILE *f = fopen(fileName, "w");
	if (f == NULL) return -1;
	//while (count-- > 0) 
	//{
	//	// you might want to check for out-of-disk-space here, too 
	//	fprintf(f, "%f\n", &data);
	//	++data;
	//}
	for (int i = 0; i < count; ++i)
	{
		fprintf(f, "%f,%f\n", data1[i],data2[i]);
	}

	fclose(f);
	return 0;
}