#include "multilayer_perceptron_c.h"

void perceptronML_init(PerceptronML* perceptron, double input) {
	time_t t;
	srand((unsigned)time(&t));

	perceptron->error = 1;

	perceptron->learningRate = 0.1;
	vector1 tempVec;
	init_vector(&tempVec);
	append_vector(&tempVec, input);
	append_vector2(&perceptron->a0, create_vector(&tempVec));

	init_vector3(&perceptron->w);
	init_vector2(&perceptron->b);

	perceptronML_generateWeightBias(perceptron, 1, 2);
	perceptronML_generateWeightBias(perceptron, 2, 1);
}

void perceptronML_feedInput(PerceptronML* perceptron, double value) {
	vector1 tempVec;
	init_vector(&tempVec);
	append_vector(&tempVec, value);
	append_vector2(&perceptron->a0, create_vector(&tempVec));
}

void perceptronML_generateWeightBias(PerceptronML* perceptron, int input, int output) {
	vector2 tempWeight;
	vector1 row;
	init_vector(&row);
	init_vector2(&tempWeight);
	for (int y = 0; y < output; y++) {
		for (int x = 0; x < input; x++) {
			append_vector(&row, (double)(rand() % 210 - 100) / 100);
			//printf("%f\n", row.array[x]);
		}

		append_vector2(&tempWeight, create_vector(&row));
		clear_vector(&row);
	}

	vector1 tempBias;
	init_vector(&tempBias);
	for (int y = 0; y < output; y++) {
		append_vector(&tempBias, (double)(rand() % 210 - 100) / 100);
	}

	append_vector3(&perceptron->w, create_vector2(&tempWeight));
	clear_vector2(&tempWeight);

	append_vector2(&perceptron->b, create_vector(&tempBias));
	clear_vector(&tempBias);
}

void perceptronML_run(PerceptronML* perceptron) {
	vector3 a;
	init_vector3(&a);
	vector2 tempA;
	init_vector2(&tempA);

	for (int x = 0; x < perceptron->w.size; x++) {
		if (x == 0) {
			tempA = perceptronML_feedForward(perceptron->a0, perceptron->w.array[x], perceptron->b.array[x], 1);
		}
		else {
			tempA = perceptronML_feedForward(a.array[x - 1], perceptron->w.array[x], perceptron->b.array[x], 0);
		}
		append_vector3(&a, create_vector2(&tempA));
	}
}

vector2 perceptronML_feedForward(vector2 input, vector2 weight, vector1 bias, int function) {
	vector2 product;
	init_vector2(&product);
	vector1 row;
	init_vector(&row);

	double total = 0;
	for (int y = 0; y < weight.size; y++) {
		for (int x = 0; x < input.array[0].size; x++) {
			for (int inner = 0; inner < weight.array[0].size; inner++) {
				total += weight.array[y].array[inner] * input.array[inner].array[x];
			}

			total = perceptronML_activation(function, total + bias.array[y]);
			append_vector(&row, total);
			total = 0;
		}
		append_vector2(&product, create_vector(&total));
		clear_vector(&row);
	}

	return product;
}

double perceptronML_activation(int function, double value) {
	switch (function) {
	case 0:
		//Linear
		return value;
	case 1:
		//Log-Sigmoid
		return 1 / (1 + pow(2.71828182845904523536, -value));
	default:
		break;
	}
}