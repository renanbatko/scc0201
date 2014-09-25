#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

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

//pesquisa o indice em table de um caracter ch
float seek_index(char ch, char *table){
	int i;
	for (i = 0; i <= strlen(table); i++) {
		//printf("%c == %c ?\n", ch, table[i]);
		if (ch == table[i]) {
			return (i * 1.0);
		}
	}
	return -1;
}

//calcula a matriz inversa
void calculate_inverse_matrix(float **m, int size) {
	int i, j, k;
	
	float ratio, a;
	for (i = 0; i < size; i++) {
		for (j = size; j < 2*size; j++) {
			if (i == (j - size)) {
				m[i][j] = 1.0;
			}
			else {
				m[i][j] = 0.0;
			}
		}
	}
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i != j) {
				ratio = m[j][i]/m[i][i];
				for (k = 0; k < 2*size; k++) {
					m[j][k] -= ratio * m[i][k];
				}
			}
		}
	}
	
	for (i = 0; i < size; i++) {
		a = m[i][i];
		for (j = 0; j < 2*size; j++) {
			m[i][j] /= a;
		}
	}
	
	int ii = 0, jj = 0;
	for (i = 0; i < size; i++) {
		for (j = size; j < 2*size; j++) {
			m[ii][jj] = m[i][j];
			jj++;
		}
		jj = 0;
		ii++;
	}
}

//multiplica a matriz m pela y e armazena o resultado na matriz x
void matrix_multiplication(float **x, float **m, float **y, int size) {
	int li, col, i;
	float s;
	for (li = 0; li < size; li++) {
		for (col = 0; col < size; col++) {
			s = 0.0;
			for (i = 0; i < size; i++) {
				s = s + (m[li][i] * y[i][col]);
			}
			x[li][col] = s;
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *fp;
	int i, j;
	char *filename;
	
	//le o nome do arquivo e abre-o
	filename = readline(stdin);
	fp = fopen(filename, "r+");
	if (fp == NULL) exit(1);
	
	char c;
	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
	}
	
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
	fseek(fp, 0, SEEK_SET);
	int k = k_value(fp);

	//y = mensagem criptografada (a que esta no arquivo)
	float **y;
	y = (float **) malloc(k * sizeof(float *));
	for (i = 0; i < k; i++) {
		y[i] = (float *) malloc(k * sizeof(float));
	}
	
	char ch;
	fseek(fp, 0, SEEK_SET);
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			ch = fgetc(fp);
			y[i][j] = seek_index(ch, table);
			//printf("%f\n", y[i][j]);
		}
	}
	
	//aloca a matriz m de dimensao k
	float **m;
	m = (float **) malloc(k * sizeof(float *));
	for (i = 0; i < k; i++) {
		m[i] = (float *) malloc(k * sizeof(float));
	}
	
	//aloca a matriz mi de dimensao k
	//float **mi;
	//mi = (float **) malloc(k * sizeof(float *));
	//for (i = 0; i < k; i++) {
	//	mi[i] = (float *) malloc(k * sizeof(float));
	//}
	
	//le os valores da matriz m
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			scanf(" %f", &m[i][j]);
		}
	}
	
	//for (i = 0; i < k; i++) {
	//	for (j = 0; j < k; j++) {
	//		printf("%d ", m[i][j]);
	//	}
	//	printf("\n");
	//}
	
	calculate_inverse_matrix(m, k);
	
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			printf("%.2f ", m[i][j]);
		}
		printf("\n");
	}
	
	//aloca a matriz resposta x de dimensao k
	float **x;
	x = (float **) malloc(k * sizeof(float *));
	for (i = 0; i < k; i++) {
		x[i] = (float *) malloc(k * sizeof(float));
	}
	
	matrix_multiplication(x, m, y, k);
	
	printf("\n");
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			printf("%.2f ", x[i][j]);
		}
		printf("\n");
	}
	
	free(filename);
	free(m);
	free(y);
	free(x);
	free(table);
	fclose(fp);
	
	return 0;
}
