#include <stdlib.h>
#include <stdio.h>

//funcao apenas para testes
/*void imprimetudo(double **mat, double *vet, int dim){
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
}*/

void gauss(double **mat, double *vet, double *x, int dim){
	int k, i, j;
	for (k = 0; k < dim-1; k++){
		for (i = k+1; i < dim; i++){
			for (j = k+1; j < dim; j++){
				mat[i][j] = mat[i][j] - ((mat[i][k] * mat[k][j])/(mat[k][k]));
			}
			vet[i] = vet[i] - ((mat[i][k] * vet[k])/(mat[k][k]));
		}
	}
	
	x[dim-1] = vet[dim-1]/mat[dim-1][dim-1];

	for (i = dim-2; i >= 0; i--){
		double s = 0;
		for (j = i+1; j < dim; j++){
			s = s + mat[i][j] * x[j];
		}
		x[i] = (vet[i] - s)/mat[i][i];
	}
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
	
	//alocacao do vetor x
	double *x;
	x = (double *) malloc(dim * sizeof(double));
	
	//leitura dos elementos do vetor resposta
	for (i = 0; i < dim; i++){
		scanf(" %lf", &vet[i]);
	}
	
	//imprimetudo(mat, vet, dim);
	
	gauss(mat, vet, x, dim);
	
	//resultados
	for (i = 0; i < dim; i++){
		printf("%.5lf\n", x[i]);
	}
	
	//matriz aumentada
	/*for (i = 0; i < dim; i++){
		mat[i][dim] = vet[i];
	}*/
	
	//imprimetudo(mat, vet, dim);
	
	//liberacao de memoria
	free(x);
	free(vet);
	for (i = 0; i < dim; i++){
		free(mat[i]);
	}
	free(mat);
	
	return 0;
}
