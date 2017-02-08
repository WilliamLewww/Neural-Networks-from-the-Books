#include <stdlib.h>
#include <stdio.h>

#ifndef MULTILAYER_PERCEPTRON_C
#define MULTILAYER_PERCEPTRON_C

#define PI 3.14159265
#define e = 2.71828182845904523536;

typedef struct ArrayWithSize {
	double*** d3;
	double** d2;
	double* d1;

	int size[3];
	int dimensions;
} ArrayWithSize;

typedef struct PerceptronML {
	double learningRate;

	ArrayWithSize w;
	int weightLength;

	ArrayWithSize b;
	int biasLength;

	double a0[1][1];

} PerceptronML;

void perceptronML_feedInput(PerceptronML*, double);
void perceptronML_init(PerceptronML*, double);
void perceptronML_generateWeightBias(PerceptronML*, int, int);

#endif