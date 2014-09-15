#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void imprime_mat(double **mat, int n){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < 4; j++){
			mat[i][j] = 5;
			printf("%lf ", mat[i][j]);
		}
		printf("\n");
	}
}

void gera_eq(double x, double y){
	//y = ax^3 + bx^2 + cx + d
	
}

int main(void){
	int n;
	scanf(" %d", &n);
	
	double *vet;
	vet = (double *) malloc(2*n*sizeof(double));
	
	int i;
	for (i = 0; i < 2*n; i++){
		scanf(" %lf", &vet[i]);
	}
	
	for (i = 0; i < 2*n; i = i + 2){
		gera_eq(vet[i], vet[i+1]);
	}
	
	double **mat;
	mat = (double **) malloc(4*sizeof(double *));
	for (i = 0; i < n; i++){
		mat[i] = (double *) malloc(n*sizeof(double));
	}
	
	imprime_mat(mat, n);
	free(vet);
	free(mat);	
	
	return 0;
}
