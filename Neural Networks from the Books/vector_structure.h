#include <stdlib.h>

#ifndef VECTOR_STRUCTURE
#define VECTOR_STRUCTURE

typedef struct vector1 {
	double* array;
	int size;

} vector1;

void init_vector(vector1*);
void append_vector(vector1*, double);
void clear_vector(vector1*);
vector1 create_vector(vector1*);

typedef struct vector2 {
	vector1* array;
	int size;

} vector2;

void init_vector2(vector2*);
void append_vector2(vector2*, vector1);
void clear_vector2(vector2*);
vector2 create_vector2(vector2*);

typedef struct vector3 {
	vector2* array;
	int size;

} vector3;

void reverse_vector3(vector3*);
void init_vector3(vector3*);
void append_vector3(vector3*, vector2);
void clear_vector3(vector3*);
vector3 create_vector3(vector3*);

#endif