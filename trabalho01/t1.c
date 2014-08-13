//renan santos batko - nusp 8532172
#include <stdio.h>
#include <stdlib.h>

//função para calcular o fatorial
int fatorial(int n){
	if (n == 0 || n == 1)
		return 1;
		
	int fat = 1, i;
	for (i = n; i > 1; i--)
		fat = fat * i;
	return fat;
}

//função para calcular o coeficiente binomial
int coeficiente_binomial(int n, int k){	
	return fatorial(n)/(fatorial(k) * fatorial(n-k));
}

//função que calcula os valores de cada posição do triângulo
void calcula_triangulo(int n, int *vector){
	int i = 0, l, c;
	for (l = 0; l < n; l++){
		for (c = 0; c <= l; c++){
			vector[i] = coeficiente_binomial(l, c);
			i++;
		}
	}
}

//função para imprimir os elementos do triângulo
void print_triangulo(int *vector, int vector_size){
	int i;
	for (i = 0; i < vector_size; i++)
		printf("%d\n", vector[i]);
}

int main(int argc, char *argv[]){
	int n;
	scanf(" %d", &n);
	
	int vector_size = 0;
	int i;
	
	//cálculo do número de elementos que o triângulo de pascal terá
	for (i = n; i > 0; i--)
		vector_size = vector_size + i;
	
	//vetor para armazenar os valores do triângulo de pascal
	int *vector = (int *) malloc((vector_size + 1) * sizeof(int));
	
	calcula_triangulo(n, vector);
	print_triangulo(vector, vector_size);
		
	free(vector);
	return 0;
}
