#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char *command = NULL;
	char ch;
	int counter = 1;
	while (ch != '\n') {
		ch = fgetc(stdin);
		command = (char *) realloc(command, counter * sizeof(char));
		command[counter-1] = ch;
		counter++;
	}
	command[counter-1] = '\0';
	
	//printf("comando: %s", command);
	
	free(command);
	return 0;
}

