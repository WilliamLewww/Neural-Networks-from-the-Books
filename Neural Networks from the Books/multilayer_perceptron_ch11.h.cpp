#include "multilayer_perceptron_ch11.h"

void PerceptronML::Run() {
	FeedForward(a0, w1, b1, 0);
}

std::vector<std::vector<double>> PerceptronML::FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total;
	for (int y = 0; y < weight.size(); y++) {
		for (int x = 0; x < input[0].size(); x++) {
			for (int inner = 0; inner < weight[0].size(); inner++) {
				total = Activation(function, (weight[y][inner] * input[inner][x]) + bias[y]);
				row.push_back(total);
			}
		}
		product.push_back(row);
		row.clear();
	}

	return weight;
}

double PerceptronML::Activation(int function, double value) {
	switch (function) {
	case 0:
		return logsig(value);
		break;
	default:
		break;
	}
}

double PerceptronML::logsig(double value) {
	return 1 / (1 + std::pow(e, -value));
}