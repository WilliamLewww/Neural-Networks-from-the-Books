#include "hopfield_network.h"

double* Hopfield::Run(double input[]) {
	double* a;
	double b[3], c[3];
	b[0] = input[0]; b[1] = input[1]; b[2] = input[2];

	bool sameResult = false;

	while (sameResult == false) {
		a = Recurrent(b);
		b[0] = a[0]; b[1] = a[1]; b[2] = a[2];

		a = satlins(b);
		b[0] = a[0]; b[1] = a[1]; b[2] = a[2];

		if (b[0] == c[0] && b[1] == c[1] && b[2] == c[2]) { sameResult = true; }

		c[0] = b[0]; c[1] = b[1]; c[2] = b[2];
	}

	return b;
}

double* Hopfield::Recurrent(double* input) {
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

double* Hopfield::satlins(double* input) {
	double net[sizeof(weight) / sizeof(*weight)] = {};
	for (int x = 0; x < (sizeof(weight) / sizeof(*weight)); x++) {
		net[x] = input[x];
		if (input[x] < -1.0) { net[x] = -1.0; }
		if (input[x] > 1.0) { net[x] = 1.0; }

		//std::cout << net[x] << std::endl;
	}

	return net;
}