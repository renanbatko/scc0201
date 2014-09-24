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

//calcula o valor de k, que eh a raiz quadrada do 
// numero de caracteres do arquivo
int k_value(FILE *fp) {
	int k = 0;
	while (fgetc(fp) != EOF) {
		k++;
	}
	return sqrt(k);
}

//calcula a matriz inversa
void calculate_inverse_matrix(int **m, int **mi, int k) {
	int **id, i;
	//aloca e preenche a matriz identidade de dimensao k
	id = (int **) malloc(k * sizeof(int *));
	for (i = 0; i < k; i++) {
		id[i] = (int *) malloc(k * sizeof(int));
	}
	int j;
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			if (i == j){
				id[i][j] = 1;
			}
			else {
				id[i][j] = 0;
			}
		}
	}
	
	//for (i = 0; i < k; i++) {
	//	for (j = 0; j < k; j++) {
	//		printf("%d ", id[i][j]);
	//	}
	//	printf("\n");
	//}
	
	//aloca memoria para o resultado de m x id
	mi = (int **) realloc(mi, k * sizeof(int *));
	for (i = 0; i < k; i++) {
		mi[i] = (int *) malloc(k * sizeof(int));
	}
	
	
	
	free(id);
}

int main(int argc, char *argv[]) {
	FILE *fp;
	int i;
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
	
	//atribui a k o valor calculado para o mesmo
	int k = k_value(fp);
	
	//aloca a matriz de dimensao k
	int **m;
	m = (int **) malloc(k * sizeof(int *));
	for (i = 0; i < k; i++) {
		m[i] = (int *) malloc(k * sizeof(int));
	}
	
	//le os valores da matriz m
	int j;
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			scanf(" %d", &m[i][j]);
		}
	}
	
	//for (i = 0; i < k; i++) {
	//	for (j = 0; j < k; j++) {
	//		printf("%d ", m[i][j]);
	//	}
	//	printf("\n");
	//}
	
	int **mi = NULL;
	calculate_inverse_matrix(m, mi, k);
	
	free(filename);
	free(m);
	free(table);
	fclose(fp);
	
	return 0;
}
