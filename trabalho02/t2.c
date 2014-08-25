#include <stdlib.h>
#include <stdio.h>

void imprimetudo(double **mat, double *vet, int dim){
	int i, j;
	printf("Matriz: \n");
	for (i = 0; i < dim; i++){
		for (j = 0; j < dim; j++){
			printf("%.5lf ", mat[i][j]);
		}
		printf("\n");
	}
	
	printf("Vetor: \n");
	for (i = 0; i < dim; i++){
		printf("%.5lf ", vet[i]);
	}
	
	printf("\n");
}

int main(void){
	int dim, i, j;
	scanf(" %d", &dim);
	
	//alocacao da matriz
	double **mat;
	mat = (double **) malloc(dim * sizeof(double *));
	for (i = 0; i < dim; i++){
		mat[i] = (double *) malloc(dim * sizeof(double));
	}
	
	//leitura dos elementos da matriz
	for (i = 0; i < dim; i++){
		for (j = 0; j < dim; j++){
			scanf(" %lf", &mat[i][j]);
		}
	}
	
	//alocacao do vetor resposta
	double *vet;
	vet = (double *) malloc(dim * sizeof(double));
	
	//leitura dos elementos do vetor resposta
	for (i = 0; i < dim; i++){
		scanf(" %lf", &vet[i]);
	}
	
	imprimetudo(mat, vet, dim);
	
	return 0;
}