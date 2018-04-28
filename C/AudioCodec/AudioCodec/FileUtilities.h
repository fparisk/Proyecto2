#ifndef FILEUTILS
#define FILEUTILS
#pragma warning(disable:4996)
#include <stdio.h> 

int WriteSingleColumn(int count, float *data, char const *fileName);
int WriteDualColumn(int count, float *data1, float *data2, char const *fileName);

#endif