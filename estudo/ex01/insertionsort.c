#include <stdio.h>
#include <stdlib.h>

void print_vector(int *vet, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d ", vet[i]);
	}
	printf("\n");
}

void insertion_sort(int *vet, int size) {
	int i, j, temp;
	for (j = 1; j < size; j++) {
		temp = vet[j];
		i = j - 1;
		while (i >= 0 && vet[i] > temp) {
			vet[i+1] = vet[i];
			i--;
		}
		vet[i+1] = temp;
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
	insertion_sort(vet, size);
	print_vector(vet, size);
	
	free(vet);
	
	return 0;
}
