#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ENTER 10

//funcao para ler um comando
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

//funcao que recebe uma linha inteira e retorna qual comando
// que estah presente nela.
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
	
	if (!strcmp(command, "insert")) return 1;
	if (!strcmp(command, "search")) return 2;
	if (!strcmp(command, "index")) return 3;
	if (!strcmp(command, "exit")) return 4;
	
	
	return -1;
}

//funcao para ler uma linha. 
// como a funcao read_command jah faz isso,
// a read_line apenas chama a read_command.
char *read_line() {
	return read_command();
}

//funcao que interpreta as informacoes do
// arquivo de metadados e cria o arquivo .reg
void create_reg_file(FILE *metadata, FILE *file_reg) {
	char *name_reg_file = NULL;
	char ch, ch2;
	rewind(metadata);
	
	int flag = 0, counter = 0;
	while ((ch = fgetc(metadata)) != ENTER) {
		if (ch == ' ') flag = 1;
		if (ch2 == ' ') flag = 2;
		ch2 = ch;
		if (flag == 2) {
			name_reg_file = (char *) realloc(name_reg_file, (counter+1) * sizeof(char));
			name_reg_file[counter] = ch;
			counter++;
		}
	}
	name_reg_file[counter] = '\0';
	
	file_reg = fopen(name_reg_file, "a");
	if (file_reg == NULL) return;
	
	
	free(name_reg_file);
}

int insert(FILE *metadata, FILE *file_reg, char *command) {
	return 0;
}

int main(int argc, char *argv[]) {	
	char *command;
	
	char *filename;
	filename = read_line();
	
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) exit(1);
	
	FILE *file_reg = NULL;
	
	while (1) {
		command = read_command();
		switch (verify_command(command)) {
			case 1:
				create_reg_file(fp, file_reg);
				insert(fp, file_reg, command);
			break;
			case 2:
				printf("search\n");
			break;
			case 3:
				printf("index\n");
			break;
			case 4:
				fclose(fp);
				free(command);
				free(filename);
				return 0;
			break;
		}
		free(command);
	}
	
	free(filename);
	return 0;
}

