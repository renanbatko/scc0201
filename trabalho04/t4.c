#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//funcao para ler do teclado
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

//funcao para preencher o vetor de caracteres
void fill_table(char *table) {
	table[0] = ' ';
	int i, k = 1;
	for (i = 97; i < 123; i++) {
		table[k] = i;
		k++;
	}
	for (i = 65; i < 91; i++) {
		table[k] = i;
		k++;
	}
	for (i = 48; i < 58; i++) {
		table[k] = i;
		k++;
	}
	for (i = 58; i < 65; i++) {
		table[k] = i;
		k++;
	}
	for (i = 33; i < 48; i++) {
		table[k] = i;
		k++;
	}
	table[k] = '[';
	k++;
	table[k] = '\\';
	k++;
	table[k] = ']';
	k++;
	table[k] = '_';
	k++;
	table[k] = '{';
	k++;
	table[k] = '|';
	k++;
	table[k] = '}';
	k++;
}

int k_value(FILE *fp) {
	int k = 0;
	while (fgetc(fp) != EOF) {
		k++;
	}
	return sqrt(k);
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *filename;
	
	//le o nome do arquivo e abre-o
	filename = readline(stdin);
	fp = fopen(filename, "r+");
	if (fp == NULL) exit(1);
	
	//aloca e preenche o vetor com os caracteres
	char *table;
	table = (char *) malloc(91 * sizeof(char));
	fill_table(table);
	
	//imprime o vetor de caracteres, apenas para testes
	//int i;
	//for (i = 0; i <= 91; i++) {
	//	printf("%c ", table[i]);
	//}
	
	//printf("k = %d\n", k_value(fp));
	
	free(filename);
	fclose(fp);
	
	return 0;
}
