#include <stdlib.h>

#ifndef VECTOR_STRUCTURE
#define VECTOR_STRUCTURE

typedef struct vector1 {
	double* array;
	int size;

} vector1;

void init_vector(vector1*);
void append_vector(vector1*, double);

typedef struct vector2 {
	vector1* array;
	int size;

} vector2;

void init_vector2(vector2*);
void append_vector2(vector2*, vector1);

typedef struct vector3 {
	vector2* array;
	int size;

} vector3;

void init_vector3(vector3*);
void append_vector3(vector3*, vector2);

#endif