#include "multilayer_perceptron_c.h"

void perceptronML_init(PerceptronML* perceptron, double input) {
	time_t t;
	srand((unsigned)time(&t));

	perceptron->learningRate = 0.1;
	perceptron->a0[0][0] = input;

	init_vector3(&perceptron->w);
	init_vector2(&perceptron->b);

	vector1 test;
	init_vector(&test);
	append_vector(&test, 5);
	append_vector(&test, 2);
	append_vector(&test, 12);
	printf("%f\n", test.array[0]);
	printf("%f\n", test.array[1]);
	printf("%f\n", test.array[2]);
	printf("%d\n", test.size);
	clear_vector(&test);
	printf("%d\n", test.size);

	//perceptronML_generateWeightBias(perceptron, 1, 2);
	//perceptronML_generateWeightBias(perceptron, 2, 1);
}

void perceptronML_feedInput(PerceptronML* perceptron, double value) {
	perceptron->a0[0][0] = value;
}

void perceptronML_generateWeightBias(PerceptronML* perceptron, int input, int output) {
	vector2 tempWieght;
	vector1 row;
	init_vector(&row);
	init_vector2(&tempWieght);
	for (int y = 0; y < output; y++) {
		for (int x = 0; x < input; x++) {
			append_vector(&row, (double)(rand() % 210 - 100) / 100);
		}

		append_vector2(&tempWieght, row);
		clear_vector(&row);
	}

	vector1 tempBias;
	for (int y = 0; y < output; y++) {
		append_vector(&tempBias, (double)(rand() % 210 - 100) / 100);
	}

	append_vector3(&perceptron->w, tempWieght);
	clear_vector2(&tempWieght);

	append_vector2(&perceptron->b, tempBias);
	clear_vector(&tempBias);
}

double*** copyArray(double*** parent, int sizeZ, int* sizeY, int** sizeX) {
	double*** tempArray = malloc(sizeZ * sizeof(double));
	for (int z = 0; z < sizeZ; z++) {
		tempArray[z] = malloc(sizeY[z] * sizeof(double));
		for (int y = 0; y < sizeY[z]; y++) {
			tempArray[z][y] = malloc(sizeX[z][y] * sizeof(double));
			for (int x = 0; x < sizeX[z][y]; x++) {
				tempArray[z][y][x] = parent[z][y][x];
			}
		}
	}

	return tempArray;
}