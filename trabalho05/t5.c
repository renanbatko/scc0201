#include <stdio.h>
#include <stdlib.h>

struct a {
	float value;
	int index;
};

void calculate_group_index(float *vet_groups, int n_groups, int *byte_index, unsigned char *bytes, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		struct a *aux;
		aux = (struct a *) malloc(sizeof(struct a));
		for (j = 0; j < n_groups; j++) {
			float dif;
			if (j == 0) {
				dif = ((bytes[i] - vet_groups[j]) >= 0) ? (bytes[i] - vet_groups[j]) : ((bytes[i] - vet_groups[j])*-1);
				aux->value = dif;
				aux->index = j;
			}
			else {
				dif = ((bytes[i] - vet_groups[j]) >= 0) ? (bytes[i] - vet_groups[j]) : ((bytes[i] - vet_groups[j])*-1);
				if (dif < aux->value) {
					aux->value = dif;
					aux->index = j;
				}
			}
		}
		byte_index[i] = aux->index;
		free(aux);
	}
}

int main(int argc, char *argv[]) {
	char audio_name[20];
	scanf(" %s", audio_name);
	
	FILE *audio;
	audio = fopen(audio_name, "r+");
	if (audio == NULL) exit(1);
	
	int counter;
	counter = 0;
	unsigned char *bytes;
	bytes = (unsigned char *) malloc(sizeof(unsigned char));
	while (fread(&bytes[counter], sizeof(unsigned char), 1, audio)) {
		//printf("%u\n", bytes[counter]);
		counter++;
		bytes = (unsigned char *) realloc(bytes, (counter + 1) * sizeof(unsigned char));
	}
	
	int n_groups;
	scanf(" %d", &n_groups);
	float *vet_groups;
	vet_groups = (float *) malloc((n_groups + 1) * sizeof(float));
	
	int i;
	for (i = 0; i < n_groups; i++) {
		scanf(" %f", &vet_groups[i]);
	}
	
	int *byte_index;
	byte_index = (int *) malloc((counter + 1) * sizeof(int));
	
	calculate_group_index(vet_groups, n_groups, byte_index, bytes, counter + 1);
	
	for (i = 0; i < counter+1; i++) {
		printf("[%u %d] ", bytes[i], byte_index[i]);
	}
	printf("\n");
	
	free(bytes);
	free(vet_groups);
	free(byte_index);
	fclose(audio);
	
	return 0;
}
