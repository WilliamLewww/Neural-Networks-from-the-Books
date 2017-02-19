#include "vector_structure.h"

void init_vector(vector1* vector) {
	vector->size = 0;
}

void clear_vector(vector1* vector) {
	free(vector->array);
}

void append_vector(vector1* vector, double element) {
	if (vector->size == 0) {
		vector->array = malloc(sizeof(double));
		vector->array[vector->size] = element;
	}
	else {
		vector->array = realloc(vector->array, (vector->size + 1) * sizeof(double));
		vector->array[vector->size] = element;
	}

	//printf("%f\n", vector->array[vector->size]);
	//printf("%f\n", vector->array[vector->size + 1]);

	vector->size += 1;
}

void init_vector2(vector2* vector) {
	vector->size = 0;
}

void clear_vector2(vector2* vector) {
	for (int x = 0; x < vector->size; x++) {
		free(vector->array[x].array);
	}
	free(vector->array);
}

void append_vector2(vector2* vector, vector1 element) {
	if (vector->size == 0) {
		vector->array = malloc(sizeof(double));
		vector->array[vector->size] = element;
	}
	else {
		vector->array = realloc(vector->array, (vector->size + 1) * sizeof(double));
		vector->array[vector->size] = element;
	}

	//printf("%f\n", vector->array[vector->size]);
	//printf("%f\n", vector->array[vector->size + 1]);

	vector->size += 1;
}

void init_vector3(vector3* vector) {
	vector->size = 0;
}

void clear_vector3(vector3* vector) {
	for (int x = 0; x < vector->size; x++) {
		for (int y = 0; y < vector->array[x].size; y++) {
			free(vector->array[x].array[y].array);
		}
		free(vector->array[x].array);
	}
	free(vector->array);
}

void append_vector3(vector3* vector, vector2 element) {
	if (vector->size == 0) {
		vector->array = malloc(sizeof(double));
		vector->array[vector->size] = element;
	}
	else {
		vector->array = realloc(vector->array, (vector->size + 1) * sizeof(double));
		vector->array[vector->size] = element;
	}

	//printf("%f\n", vector->array[vector->size]);
	//printf("%f\n", vector->array[vector->size + 1]);

	vector->size += 1;
}