#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265

void dct2(unsigned char *bytes, float *new_bytes, int size) {
	int i, k;
	for (k = 0; k < size; k++) {
		new_bytes[k] = 0;
		for (i = 0; i < size; i++) {
			new_bytes[i] += ((bytes[i] * 1.0) * cos((PI/size) * (i + 0.5) * k));
		}
	}
}

int main(int argc, char *argv[]) {
	char audio_name[20];
	scanf(" %s", audio_name);
	
	int K;
	scanf(" %d", &K);
	
	FILE *audio;
	audio = fopen(audio_name, "r");
	if (audio == NULL) exit(1);
	
	int counter;
	counter = 0;
	unsigned char *bytes;
	bytes = (unsigned char *) malloc(sizeof(unsigned char));
	while (fread(&bytes[counter], sizeof(unsigned char), 1, audio)) {
		counter++;
		bytes = (unsigned char *) realloc(bytes, (counter + 1) * sizeof(unsigned char));
	}
	int size;
	size = counter;
	
	float *new_bytes;
	new_bytes = (float *) malloc((size + 1) * sizeof(float));
	
	dct2(bytes, new_bytes, size);
	
	free(bytes);
	free(new_bytes);
	
	return 0;
}

