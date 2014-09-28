#include <stdio.h>
#include <stdlib.h>

void print_vector(int *vet, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d ", vet[i]);
	}
	printf("\n");
}

void swap(int *vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

void bubble_sort(int *vet, int size) {
	int i, j;
	for (i = 1; i < size; i++) {
		for (j = 0; j < size-i; j++) {
			if (vet[j+1] < vet[j]) {
				swap(vet, j, j+1);
			}
		}
	}
}

int main(void) {
	
	int *vet, i, size;
	scanf(" %d", &size);
	
	vet = (int *) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		vet[i] = rand() % 100;
	}
	
	print_vector(vet, size);
	bubble_sort(vet, size);
	print_vector(vet, size);
	
	free(vet);
	
	return 0;
}
