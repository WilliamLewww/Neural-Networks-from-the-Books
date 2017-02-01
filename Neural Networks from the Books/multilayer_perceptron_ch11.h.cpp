#include "multilayer_perceptron_ch11.h"

void PerceptronML::InitializeWeightBias() {
	for (int x = 0; x < w1.size(); x++) {
		w1[x][0] = (double)(rand() % 210 - 100) / 100;
	}

	for (int x = 0; x < w2[0].size(); x++) {
		w2[0][x] = (double)(rand() % 210 - 100) / 100;
	}

	for (int x = 0; x < b1.size(); x++) {
		b1[x] = (double)(rand() % 210 - 100) / 100;
	}

	for (int x = 0; x < b2.size(); x++) {
		b2[x] = (double)(rand() % 210 - 100) / 100;
	}
}

void PerceptronML::GenerateWeightBias(int input, int output, int biasCount) {
	std::vector<std::vector<double>> tempWeight;
	std::vector<double> row;
	for (int y = 0; y < output; y++) {
		for (int x = 0; x < input; x++) {
			row.push_back((double)(rand() % 210 - 100) / 100);
		}

		tempWeight.push_back(row);
	}

	std::vector<double> tempBias;
	for (int x = 0; x < biasCount; x++) {
		tempBias.push_back((double)(rand() % 210 - 100) / 100);
	}

	w.push_back(tempWeight);
	b.push_back(tempBias);
}

void PerceptronML::FeedInput(double input) {
	a0 = { { input } };
	error = 1;
}

void PerceptronML::Initialize(double input) {
	srand(time(0));

	a0 = { { input } };
	w1 = { { -0.27 }, { -0.41 } };
	b1 = { -0.48, -0.13 };
	w2 = { { 0.09, -0.17 } };
	b2 = { 0.48 };

	InitializeWeightBias();

	error = 1;
}

double PerceptronML::Calculate(double input) {
	std::vector<std::vector<double>> a1 = FeedForward(a0, w1, b1, 1);
	std::vector<std::vector<double>> a2 = FeedForward(a1, w2, b2, 0);
	std::vector<std::vector<std::vector<double>>> a = { a1, a2 };

	error = OriginalFunction(a0[0][0]) - a2[0][0];
	std::cout << error << "||" << a2[0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;

	return a2[0][0];
}

void PerceptronML::Run() {
	std::vector<std::vector<double>> a1 = FeedForward(a0, w1, b1, 1);
	std::vector<std::vector<double>> a2 = FeedForward(a1, w2, b2, 0);
	std::vector<std::vector<std::vector<double>>> a = { a1, a2 };

	error = OriginalFunction(a0[0][0]) - a2[0][0];
	Backpropagation(error, a);

	//std::cout << floor(error * 10000 + 0.5) / 10000 << std::endl;
	std::cout << error << "||" << a2[0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;
}

void PerceptronML::Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input) {
	std::vector<double> s2 = { -2 * (DActivation(0, input[1][0][0])) * error };
	std::vector<std::vector<double>> f1 = { { DActivation(1, input[0][0][0]), 0 }, { 0, DActivation(1, input[0][1][0]) } };
	std::vector<std::vector<double>> w2new = { { s2[0] * w2[0][0]}, { s2[0] * w2[0][1] } };
	std::vector<std::vector<double>> s1 = MultMatrix(w2new, f1);

	w2[0][0] = w2[0][0] - (0.1 * s2[0] * input[0][0][0]);
	w2[0][1] = w2[0][1] - (0.1 * s2[0] * input[0][1][0]);
	b2[0] = b2[0] - (0.1 * s2[0]);

	w1[0][0] = w1[0][0] - (0.1 * s1[0][0] * a0[0][0]);
	w1[1][0] = w1[1][0] - (0.1 * s1[1][0] * a0[0][0]);
	b1[0] = b1[0] - (0.1 * s1[0][0]);
	b1[1] = b1[1] - (0.1 * s1[1][0]);
}

std::vector<std::vector<double>> PerceptronML::MultMatrix(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total = 0;;
	for (int y = 0; y < matB.size(); y++) {
		for (int x = 0; x < matA[0].size(); x++) {
			for (int inner = 0; inner < matB[0].size(); inner++) {
				total += matB[y][inner] * matA[inner][x];
			}
			row.push_back(total);
			total = 0;
		}
		product.push_back(row);
		row.clear();
	}

	return product;
}

std::vector<std::vector<double>> PerceptronML::FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total = 0;;
	for (int y = 0; y < weight.size(); y++) {
		for (int x = 0; x < input[0].size(); x++) {
			for (int inner = 0; inner < weight[0].size(); inner++) {
				total += weight[y][inner] * input[inner][x];
			}

			total = Activation(function, total + bias[y]);
			row.push_back(total);
			total = 0;
		}
		product.push_back(row);
		row.clear();
	}

	return product;
}

double PerceptronML::Activation(int function, double value) {
	switch (function) {
	case 0:
		//Linear
		return value;
	case 1:
		//Log-Sigmoid
		return 1 / (1 + std::pow(e, -value));
	default:
		break;
	}
}

double PerceptronML::DActivation(int function, double value) {
	switch (function) {
	case 0:
		//Linear
		return 1;
	case 1:
		//Log-Sigmoid
		return (1-value)*(value);
	default:
		break;
	}
}

double PerceptronML::OriginalFunction(double value) {
	return 1 + sin((PI / 4) * value);
}