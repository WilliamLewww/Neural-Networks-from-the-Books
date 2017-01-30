#include "multilayer_perceptron_ch11.h"

void PerceptronML::Run() {
	std::vector<std::vector<double>> a1 = FeedForward(a0, w1, b1, 1);
	std::vector<std::vector<double>> a2 = FeedForward(a1, w2, b2, 0);
	std::vector<std::vector<std::vector<double>>> a = { a1, a2 };

	double error = OriginalFunction(1) - a2[0][0];

	Backpropagation(error, a);
}

std::vector<std::vector<double>> PerceptronML::Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input) {
	std::vector<double> s2 = { -2 * (DActivation(0, input[1][0][0])) * error };

	std::vector<std::vector<double>> f1 = { { DActivation(1, input[0][0][0]), 0 }, { 0, DActivation(1, input[0][1][0]) } };
	std::vector<std::vector<double>> w2new = { { s2[0] * w2[0][0]}, { s2[0] * w2[0][1] } };
	std::vector<std::vector<double>> s1 = FeedForward(w2new, f1);

	std::cout << s1[0][0] << ":" << s1[1][0] << std::endl;

	std::vector<std::vector<double>> exit;
	return exit;
}

std::vector<std::vector<double>> PerceptronML::FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total = 0;;
	for (int y = 0; y < weight.size(); y++) {
		for (int x = 0; x < input[0].size(); x++) {
			for (int inner = 0; inner < weight[0].size(); inner++) {
				total += weight[y][inner] * input[inner][x];
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