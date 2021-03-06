#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//funcao apenas para testes
/*void imprime(double **mat, double *vet, int n){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < 3; j++){
			printf("%lf ", mat[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	for (i = 0; i < n; i++)
		printf("%lf ", vet[i]);
}*/

void gera_eq(double x, double *a, double *b, double *c, double *d){
	//y = ax^3 + bx^2 + cx + d
	*a = pow(x, 3);
	*b = pow(x, 2);
	*c = x;
	*d = 1;
}

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
	int n;
	scanf(" %d", &n);
	
	//alocacao do vetor com os valores de entrada
	//P(x, y) = P(vet[i], vet[i+1])
	double *v;
	v = (double *) malloc(2 * n * sizeof(double));
	
	//alocacao do vetor resposta
	double *vet;
	vet = (double *) malloc(n * sizeof(double));
	
	//leitura dos valores de entrada
	int i;
	for (i = 0; i < 2*n; i++){
		scanf(" %lf", &v[i]);
	}
	
	//alocacao da matriz
	double **mat;
	mat = (double **) malloc(3 * sizeof(double *));
	for (i = 0; i < n; i++){
		mat[i] = (double *) malloc(n * sizeof(double));
	}
	
	//gerando os coeficientes
	double abcd[4];
	int k = 0, j, jj = 0;
	for (i = 0; i < 2*n; i = i + 2){
		//if (i != 0)
		vet[k] = v[i+1];
		gera_eq(v[i], &abcd[0], &abcd[1], &abcd[2], &abcd[3]);
		//printf("a = %lf b = %lf c = %lf d = %lf\n", abcd[0], abcd[1], abcd[2], abcd[3]);
		for (j = 0; j < n; j++){
			mat[jj][j] = abcd[j];
		}
		jj++;
		k++;
	}
	
	//alocacao do vetor x
	double *x;
	x = (double *) malloc(n * sizeof(double));
	
	gauss(mat, vet, x, n);
	
	//impressao dos resultados
	for (i = 0; i < n; i++){
		printf("%.6lf\n", x[i]);
	}
	
	//imprime(mat, vet, n);
	free(v);
	free(x);
	free(vet);
	free(mat);	
	
	return 0;
}
