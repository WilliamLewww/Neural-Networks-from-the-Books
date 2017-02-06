#include "multilayer_perceptron_c.h"

void perceptronML_init(PerceptronML* perceptron, double input) {
	perceptron->learningRate = 0.1;
	perceptron->a0[0][0] = input;
}

void perceptronML_feedInput(PerceptronML* perceptron, double value) {
	perceptron->a0[0][0] = value;
}

//int** x;
//
//x = malloc(dimension1_max * sizeof(int*));
//for (int i = 0; i < dimension1_max; i++) {
//	x[i] = malloc(dimension2_max * sizeof(int));
//}
//
//[...]
//
//for (int i = 0; i < dimension1_max; i++) {
//	free(x[i]);
//}
//free(x);

void perceptronML_generateWeightBias(double** weight, double* bias, int input, int output) {
	weight = malloc(output * sizeof(double*));
	for (int y = 0; y < output; y++) {
		weight[y] = malloc(input * sizeof(double*));
	}
}