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

	reverse_vector3(&a);
	append_vector3(&a, create_vector2(&perceptron->a0));
	reverse_vector3(&a);

	perceptron->error = originalFunction(perceptron->a0.array[0].array[0]) - a.array[a.size - 1].array[0].array[0];
	perceptronML_backpropagation(perceptron, perceptron->error, a);

	printf("%f\n", perceptron->error);
}

void perceptronML_backpropagation(PerceptronML* perceptron, double error, vector3 input) {
	vector3 s;
	init_vector3(&s);
	int y = input.size - 1;

	for (int x = perceptron->w.size - 1; x >= 0; x--) {
		if (x == perceptron->w.size - 1) {
			vector2 tempVec2;
			init_vector2(&tempVec2);
			vector1 tempVec;
			init_vector(&tempVec);

			append_vector(&tempVec, (-2 * (perceptronML_dActivation(0, input.array[y].array[0].array[0])) * error));
			append_vector2(&tempVec2, create_vector(&tempVec));
			append_vector3(&s, create_vector2(&tempVec2));
		}
		else {
			vector2 tempVec, tempVec2, tempVec3;
			tempVec3 = perceptronML_multMatrix(perceptronML_flipMatrix(perceptron->w.array[x + 1]), s.array[s.size - 1]);
			tempVec2 = perceptronML_multMatrix(perceptronML_genJacobianMatrix(input.array[x + 1], 1), create_vector2(&tempVec3));
			append_vector3(&s, create_vector2(&tempVec2));

			//perceptronML_multMatrix(perceptronML_genJacobianMatrix(input.array[x + 1], 1), perceptronML_multMatrix(perceptronML_flipMatrix(perceptron->w.array[x + 1]), s.array[s.size - 1]));
		}

		y -= 1;
	}

	reverse_vector3(&s);

	for (int y = 0; y < perceptron->w.size; y++) {
		for (int x = 0; x < perceptron->w.array[y].size; x++) {
			for (int z = 0; z < perceptron->w.array[y].array[x].size; z++) {
				perceptron->w.array[y].array[x].array[z] = perceptron->w.array[y].array[x].array[z] - (perceptron->learningRate * perceptronML_getMatLin(x, s.array[y]));
			}
		}
	}

	for (int y = 0; y < perceptron->b.size; y++) {
		for (int x = 0; x < perceptron->b.array[y].size; x++) {
			perceptron->b.array[y].array[x] = perceptron->b.array[y].array[x] - (perceptron->learningRate * perceptronML_getMatLin(x, s.array[y]));
		}
	}
}

double perceptronML_getMatLin(int index, vector2 mat) {
	if (mat.size > mat.array[0].size) { return mat.array[index].array[0]; }
	if (mat.size < mat.array[0].size) { return mat.array[0].array[index]; }

	return mat.array[0].array[0];
}

vector2 perceptronML_flipMatrix(vector2 mat) {
	vector2 tempMat;
	init_vector2(&tempMat);
	vector1 col;
	init_vector(&col);

	for (int x = 0; x < mat.array[0].size; x++) {
		for (int y = 0; y < mat.size; y++) {
			append_vector(&col, mat.array[y].array[x]);
		}

		append_vector2(&col, create_vector(&col));
		clear_vector(&col);
	}

	return tempMat;
}

vector2 perceptronML_genJacobianMatrix(vector2 input, int function) {
	vector2 output;
	init_vector2(&output);
	vector1 row;
	init_vector(&row);

	int layer = 0;

	if (input.size > input.array[0].size) {
		layer = 1;
	}

	if (layer == 1) {
		for (int x = 0; x < input.size; x++) {
			for (int y = 0; y < input.size; y++) {
				if (y == x) {
					append_vector(&row, perceptronML_dActivation(function, input.array[0].array[x]));
				}
				else {
					append_vector(&row, 0.0);
				}
			}

			append_vector2(&output, create_vector(&row));
			clear_vector(&row);
		}
	}

	return output;
}

vector2 perceptronML_multMatrix(vector2 weight, vector2 input) {
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

			append_vector(&row, total);
			total = 0;
		}

		append_vector2(&product, create_vector(&row));
		clear_vector(&row);
	}

	return product;
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
		append_vector2(&product, create_vector(&row));
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

double perceptronML_dActivation(int function, double value) {
	switch (function) {
	case 0:
		//Linear
		return 1;
	case 1:
		//Log-Sigmoid
		return (1 - value)*(value);
	default:
		break;
	}
}

double originalFunction(double value) {
	return 1 + sin((PI / 4) * value);
}