#include "perceptron_network.h"

double Perceptron::Run(double input[]) {
	double a;
	a = FeedForward(input);

	return hardlims(a);
}

double Perceptron::FeedForward(double* input) {
	double net = 0;
	for (int y = 0; y < (sizeof(weight) / sizeof(*weight)); y++) {
		for (int x = 0; x < (sizeof(weight[0]) / sizeof(*weight[0])); x++) {
			net += input[x] * weight[y][x];
		}
		//std::cout << net << std::endl;
	}

	return net;
}

double Perceptron::hardlims(double input) {
	double net = input;

	if (net < 0) { net = -1; }
	if (net >= 0) { net = 1; }

	return net;
}