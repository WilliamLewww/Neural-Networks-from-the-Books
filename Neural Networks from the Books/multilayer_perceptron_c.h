#include <stdlib.h>
#include <stdio.h>
#include "vector_structure.h"

#ifndef MULTILAYER_PERCEPTRON_C
#define MULTILAYER_PERCEPTRON_C

#define PI 3.14159265
#define e = 2.71828182845904523536;

typedef struct PerceptronML {
	double learningRate;

	vector3 w;
	vector2 b;

	double a0[1][1];

} PerceptronML;

void perceptronML_feedInput(PerceptronML*, double);
void perceptronML_init(PerceptronML*, double);
void perceptronML_generateWeightBias(PerceptronML*, int, int);

#endif