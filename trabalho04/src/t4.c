#include <stdlib.h>
#include <stdio.h>

char *readline(FILE *stream) {
	char *buffer = NULL;
	char character;
	int counter = 0;
	
	do {
		character = fgetc(stream);
		buffer = (char *) realloc(buffer, sizeof(char) * (counter+1));
		buffer[counter++] = character;
	} while (character != 10);
	buffer[counter-1] = '\0';
	
	return buffer;
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *filename;
	
	filename = readline(stdin);
	fp = fopen(filename, "r+");
	if (fp == NULL) exit(1);
	
	free(filename);
	fclose(fp);
	
	return 0;
}
