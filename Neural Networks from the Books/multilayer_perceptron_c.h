#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector_structure.h"

#ifndef MULTILAYER_PERCEPTRON_C
#define MULTILAYER_PERCEPTRON_C

#define PI 3.14159265
//#define e 2.71828182845904523536;

typedef struct PerceptronML {
	double learningRate;

	vector3 w;
	vector2 b;

	vector2 a0;

	double error;

} PerceptronML;

void perceptronML_feedInput(PerceptronML*, double);
void perceptronML_init(PerceptronML*, double);
void perceptronML_generateWeightBias(PerceptronML*, int, int);
void perceptronML_run(PerceptronML*);
void perceptronML_backpropagation(PerceptronML* perceptron, double error, vector3 input);
vector2 perceptronML_feedForward(vector2 input, vector2 weight, vector1 bias, int function);
double perceptronML_activation(int function, double value);
double perceptronML_dActivation(int function, double value);
double originalFunction(double value);
vector2 perceptronML_genJacobianMatrix(vector2 input, int function);
vector2 perceptronML_multMatrix(vector2 weight, vector2 input);
vector2 perceptronML_flipMatrix(vector2 mat);
double perceptronML_getMatLin(int index, vector2 mat);

#endif