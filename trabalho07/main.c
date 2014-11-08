#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *next_command(FILE *stream) {
	char *buffer = NULL;
	int counter = 0;
	char ch;
	
	do {
		ch = fgetc(stream);
		buffer = (char *) realloc(buffer, (counter+1) * sizeof(char));
		counter++;
		buffer[counter-1] = ch;
	} while (ch != '\n');
	buffer[counter-1] = '\0';
	
	return buffer;
}

int main(int argc, char *argv[]) {
	char filename[20];
	scanf(" %s", filename);
	
	//FILE *mfp;
	//mfp = fopen(filename, "r");
	//if (mfp == NULL) exit(1);
	
	while (1) {
		char *command;
		command = next_command(stdin);
		printf("%s", command);
		
		//int comp = strcmp(command, "exit");
		//printf("comp = %d\n", comp);
		if (!strcmp(command, "exit")) {
			free(command);
			break;
		}
	}
	
	return 0;
}

