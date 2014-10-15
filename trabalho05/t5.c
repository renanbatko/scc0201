#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

struct b {
	float sum;
	float n;
};

void calculate_new_groups(int *byte_index, unsigned char *bytes, int size, float *new_groups, int n_groups) {
	int i, j;
	
	struct b *aux;
	aux = (struct b *) malloc((n_groups + 1) * sizeof(struct b));
	
	for (i = 0; i < n_groups; i++) {
		aux[i].sum = 0;
		aux[i].n = 0;
	}
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < n_groups; j++) {
			if (byte_index[i] == j) {
				aux[j].sum = aux[j].sum + bytes[i];
				aux[j].n++;
				break;
			}
		}
		
	}
	
	for (i = 0; i < n_groups; i++) {
		new_groups[i] = aux[i].sum/aux[i].n;
		//printf("%.2f/%.1f = %.2f\n", aux[i].sum, aux[i].n, aux[i].sum/aux[i].n);
	}
	free(aux);
}

void fill_new_bytes(float *new_bytes, int *byte_index, int size, float *new_groups) {
	int i;
	//for (i = 0; i < 3; i++) {
	//	printf("%.2f ", new_groups[i]);
	//}
	
	for (i = 0; i < size; i++) {
		new_bytes[i] = new_groups[byte_index[i]];
		//printf("%.2f ", new_bytes[i]);
	}
}

void truncate(float *new_bytes, int size) {
	int i;
	for (i = 0; i < size; i++) {
		new_bytes[i] = floor(new_bytes[i]);
		//printf("%.0f ", new_bytes[i]);
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
	float T;
	scanf(" %f", &T);
	
	int *byte_index;
	byte_index = (int *) malloc((counter + 1) * sizeof(int));
	
	calculate_group_index(vet_groups, n_groups, byte_index, bytes, counter + 1);
	
	//for (i = 0; i < counter+1; i++) {
	//	printf("[%u %d] ", bytes[i], byte_index[i]);
	//}
	//printf("\n");
	
	float *new_groups;
	new_groups = (float *) malloc((n_groups + 1) * sizeof(float));
	calculate_new_groups(byte_index, bytes, counter + 1, new_groups, n_groups);
	
	float average_dif, dif;
	struct b *aux;
	aux = (struct b *) malloc(sizeof(struct b));
	for (i = 0; i < n_groups; i++) {
		dif = (vet_groups[i]-new_groups[i] > 0) ? (vet_groups[i]-new_groups[i]) : ((vet_groups[i]-new_groups[i])*-1);
		aux->sum = aux->sum + dif;
		aux->n++;
	}
	average_dif = aux->sum/aux->n;
	//printf("average_dif: %.2f\n", average_dif);
	
	while (average_dif > T) {
		for (i = 0; i < n_groups; i++) {
			vet_groups[i] = new_groups[i];
		}
		
		calculate_group_index(vet_groups, n_groups, byte_index, bytes, counter + 1);
		calculate_new_groups(byte_index, bytes, counter + 1, new_groups, n_groups);
		
		for (i = 0; i < n_groups; i++) {
			dif = (vet_groups[i]-new_groups[i] > 0) ? (vet_groups[i]-new_groups[i]) : ((vet_groups[i]-new_groups[i])*-1);
			aux->sum = aux->sum + dif;
			aux->n++;
		}
		average_dif = aux->sum/aux->n;
		//printf("average_dif: %.2f\n", average_dif);
	}
	
	float *new_bytes;
	new_bytes = (float *) malloc((counter + 1) * sizeof(float));
	
	fill_new_bytes(new_bytes, byte_index, counter + 1, new_groups);
	
	truncate(new_bytes, counter + 1);
	
	FILE *fp;
	fp = fopen("saida.raw", "w+");
	if (fp == NULL) exit(1);
	
	for (i = 0; i < counter + 1; i++) {
		fputc(new_bytes[i], stdout);
		fputc(new_bytes[i], fp);
	}
	
	free(bytes);
	free(vet_groups);
	free(byte_index);
	free(new_groups);
	free(aux);
	free(new_bytes);
	fclose(audio);
	fclose(fp);
	
	return 0;
}
