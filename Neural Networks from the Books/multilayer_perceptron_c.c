#include "multilayer_perceptron_c.h"

void perceptronML_init(PerceptronML* perceptron, double input) {
	time_t t;
	srand((unsigned)time(&t));

	perceptron->learningRate = 0.1;
	perceptron->a0[0][0] = input;

	perceptron->weightLength = 0;
	perceptron->biasLength = 0;

	perceptron->w.dimensions = 3;
	perceptron->b.dimensions = 2;

	perceptronML_generateWeightBias(perceptron, 1, 2);
	perceptronML_generateWeightBias(perceptron, 2, 1);
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

void perceptronML_generateWeightBias(PerceptronML* perceptron, int input, int output) {
	perceptron->w.d3 = malloc(perceptron->weightLength * sizeof(double));
	perceptron->w.d3[perceptron->weightLength] = malloc(output * sizeof(double));
	for (int y = 0; y < output; y++) {
		perceptron->w.d3[perceptron->weightLength][y] = malloc(input * sizeof(double));
		for (int x = 0; x < input; x++) {
			perceptron->w.d3[perceptron->weightLength][y][x] = (double)(rand() % 210 - 100) / 100;
			printf("%f\n", perceptron->w.d3[perceptron->weightLength][y][x]);
		}
	}

	perceptron->b.d2 = malloc(perceptron->biasLength * sizeof(double));
	perceptron->b.d2[perceptron->weightLength] = malloc(output * sizeof(double));
	for (int y = 0; y < output; y++) {
		perceptron->b.d2[perceptron->biasLength][y] = (double)(rand() % 210 - 100) / 100;
	}

	perceptron->weightLength += 1;
	perceptron->biasLength += 1;
}