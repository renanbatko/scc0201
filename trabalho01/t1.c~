#include <stdio.h>
#include <stdlib.h>

int fatorial(int n){
	if (n == 0 || n == 1)
		return 1;
		
	int fat = 1, i;
	for (i = n; i > 1; i--)
		fat = fat * i;
	return fat;
}

int coeficiente_binomial(int n, int k){	
	return fatorial(n)/(fatorial(k) * fatorial(n-k));
}

int main(int argc, char *argv[]){
	int n;
	scanf(" %d", &n);
	
	int vector_size = 0;
	int i;
	
	for (i = n; i > 0; i--)
		vector_size = vector_size + i;
	
	int *vector = (int *) malloc((vector_size + 1) * sizeof(int));
	int l = 0, c = 0;
	
	i = 0;
	for (l = 0; l < n; l++){
		for (c = 0; c <= l; c++){
			vector[i] = coeficiente_binomial(l, c);
			i++;
		}
	}
	
	for (i = 0; i < vector_size; i++)
		printf("%d\n", vector[i]);
		
	free(vector);
	return 0;
}
