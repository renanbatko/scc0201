//renan santos batko - nusp 8532172
#include <stdio.h>
#include <stdlib.h>

void completa_matriz(unsigned long int **m, int n){
	unsigned long int l, c;
	for (l = 0; l < n; l++){
		for (c = 0; c <= l; c++){
			if (c == 0 || l == c){
				m[l][c] = 1;
			}
			else{
				m[l][c] = m[l-1][c-1] + m[l-1][c];
			}
		}
	}
}

void imprime_matriz(unsigned long int **m, int n){
	unsigned long int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j <= i; j++){
			printf("%lu\n", m[i][j]);
		}
	}
}

int main(void){
	int n, i;
	scanf(" %d", &n);
	
	unsigned long int **m = (unsigned long int **) malloc((n+1)*sizeof(unsigned long int *));
	for (i = 0; i < n; i++){
		m[i] = (unsigned long int *) malloc((i+1)*sizeof(unsigned long int));
	}
	
	completa_matriz(m, n);
	imprime_matriz(m, n);
	
	return 0;
}
