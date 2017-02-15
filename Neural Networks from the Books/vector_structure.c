#include "vector_structure.h"

void init_vector(vector1* vector) {
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