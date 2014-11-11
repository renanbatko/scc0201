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

int verify_command(char *full_command) {
	char *command = NULL;
	int counter = 0, i = 0;
	//printf("full_command: %s\n", full_command);
	while (full_command[i] != ' ' && full_command[i] != '\0') {
		//printf("full_command[i] = %c\n", full_command[i]);
		command = (char *) realloc(command, (counter+1) * sizeof(char));
		command[counter] = full_command[i];
		counter++;
		i++;
	}
	command[counter] = '\0';
	
	//printf("COMANDO: %s\n", command);
	
	return 1;
}

int main(int argc, char *argv[]) {
	char *command = read_command();
	
	verify_command(command);
	/*switch (verify_command(command)) {
		case 1:
			//something something
		break;
		case 2:
			//something something
		break;
		case 3:
			//something something
		break;
		case 4:
			//something something
		break;
	}*/
	
	free(command);
	return 0;
}

