#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ENTER 10

char *read_command() {
	char *command = NULL;
	char ch;
	int counter = 0;
	do {
		ch = fgetc(stdin);
		command = (char *) realloc(command, (counter+1) * sizeof(char));
		command[counter++] = ch;
	} while (ch != ENTER);
	command[counter-1] = '\0';
	
	return command;
}

int main(int argc, char *argv[]) {
	char *command = read_command();
	
	//printf("comando: %s\n", command);
	
	free(command);
	return 0;
}

