#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *next_command(FILE *stream) {
	char *buffer = NULL;
	int counter = 0;
	char ch;
	
	do {
		ch = fgetc(stream);
		buffer = (char *) realloc(buffer, (counter + 1) * sizeof(char));
		counter++;
		buffer[counter-1] = ch;
	} while (ch != '\n');
	counter++;
	buffer = (char *) realloc(buffer, (counter + 1) * sizeof(char));
	buffer[counter-1] = ' ';
	buffer[counter] = '\0';
	
	return buffer;
}

void verify_command(char *full_command) {
	if (!strcmp(full_command, "-lixo")) return;
	char *command = NULL;
	int i = 0;
	
	//printf("comando full: %s\n", full_command);
	while (full_command[i] != ' ') {
		//printf("%c", full_command[i]);
		command = (char *) realloc(command, (i + 1) * sizeof(char));
		command[i] = full_command[i];
		i++;
	}
	command[i] = '\0';
	
	int temp = strcmp(command, "index");
	printf("temp = %d\n", temp);
	printf("command: %s\n", command);
	if (!strcmp(command, "insert")) {
		printf("insert\n");
	}
	
	if (!strcmp(command, "index")) {
		printf("index\n");
	}
	
	if (!strcmp(command, "search")) {
		printf("search\n");
	}
	
	free(command);
}

int main(int argc, char *argv[]) {
	char filename[20];
	scanf(" %s", filename);
	
	//FILE *mfp;
	//mfp = fopen(filename, "r");
	//if (mfp == NULL) exit(1);
	
	int flag = 0;
	while (1) {
		char *command;
		command = next_command(stdin);
		if (flag == 0) {
			strcpy(command, "-lixo");
			flag++;
		}
		//printf("%s", command);
		
		//int comp = strcmp(command, "exit");
		//printf("comp = %d\n", comp);
		if (!strcmp(command, "exit ")) {
			free(command);
			break;
		}
		//printf("antes\n");
		verify_command(command);
		//printf("depois\n");
	}
	
	return 0;
}

