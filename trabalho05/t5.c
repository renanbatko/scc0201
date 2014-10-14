#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char audio_name[20];
	scanf(" %s", audio_name);
	
	FILE *audio;
	audio = fopen(audio_name, "r+");
	if (audio == NULL) exit(1);
	
	int counter;
	counter = 0;
	unsigned char *bytes;
	bytes = (unsigned char *) malloc(sizeof(unsigned char));
	while (fread(&bytes[counter], sizeof(unsigned char), 1, audio)) {
		printf("%u ", bytes[counter]);
		counter++;
		bytes = (unsigned char *) realloc(bytes, (counter + 1) * sizeof(unsigned char));
	}
	
	free(bytes);
	fclose(audio);
	
	return 0;
}
