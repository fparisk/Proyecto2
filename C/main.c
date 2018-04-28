#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

void getSamples()
{
	FILE *fp;
	float *a, temp = 0;
	int count = 0;
	a = (float *)malloc(300 * sizeof(int));
	fp = fopen("muestras.csv", "r");
	temp = fgetc(fp);
	while (!feof(fp))
	{
		if (temp != 44 && temp != 10 && temp != 32)
		{
			count++;
			a[count] = temp;
		}
		temp = fgetc(fp);
	}
	fclose(fp);
}


int main(int argc, char *argv[])
{
	getSamples();
	//FILE *fp_in;
	//gitfp_in = fopen("muestra.wav", "rb");
}
