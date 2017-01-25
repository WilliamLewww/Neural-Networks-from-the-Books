#include "hamming_network.h"

double* Hamming::Run(double input[]) {
	double* a;
	double b[2];

	a = FeedForward(input);
	b[0] = a[0]; b[1] = a[1];

	while (b[0] > 0 && b[1] > 0) {
		a = Recurrent(b);
		b[0] = a[0]; b[1] = a[1];
	}

	return b;
}

double* Hamming::FeedForward(double* input) {
	double net[sizeof(weight) / sizeof(*weight)] = {};
	for (int y = 0; y < (sizeof(weight) / sizeof(*weight)); y++) {
		for (int x = 0; x < (sizeof(weight[0]) / sizeof(*weight[0])); x++) {
			net[y] += input[x] * weight[y][x];
		}
		net[y] += bias[y];
		//std::cout << net[y] << std::endl;
	}

	return net;
}

double* Hamming::Recurrent(double* input) {
	double net[sizeof(weightRec) / sizeof(*weightRec)] = {};
	for (int y = 0; y < (sizeof(weightRec) / sizeof(*weightRec)); y++) {
		for (int x = 0; x < (sizeof(weightRec[0]) / sizeof(*weightRec[0])); x++) {
			net[y] += input[x] * weightRec[y][x];
		}
		//std::cout << net[y] << std::endl;
	}

	return net;
}