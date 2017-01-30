#include "multilayer_perceptron_ch11.h"

void PerceptronML::Run() {
	std::vector<std::vector<double>> a1 = FeedForward(a0, w1, b1, 1);
	FeedForward(a1, w2, b2, 0);
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