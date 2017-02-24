#include "vector_structure.h"

vector1 create_vector(vector1* vector) {
	vector1 newVector;
	newVector.size = vector->size;
	newVector.array = malloc(newVector.size * sizeof(double));
	for (int x = 0; x < newVector.size; x++) {
		newVector.array[x] = vector->array[x];
	}

	return newVector;
}

vector2 create_vector2(vector2* vector) {
	vector2 newVector;
	newVector.size = vector->size;
	newVector.array = malloc(newVector.size * sizeof(vector->array));
	for (int x = 0; x < newVector.size; x++) {
		newVector.array[x] = vector->array[x];
	}

	return newVector;
}

vector3 create_vector3(vector3* vector) {
	vector3 newVector;
	newVector.size = vector->size;
	newVector.array = malloc(newVector.size * sizeof(vector->array));
	for (int x = 0; x < newVector.size; x++) {
		newVector.array[x] = vector->array[x];
	}

	return newVector;
}

void init_vector(vector1* vector) {
	vector->size = 0;
}

void clear_vector(vector1* vector) {
	free(vector->array);
	vector->size = 0;
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
	free(vector->array);
	vector->size = 0;
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
	free(vector->array);
	vector->size = 0;
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