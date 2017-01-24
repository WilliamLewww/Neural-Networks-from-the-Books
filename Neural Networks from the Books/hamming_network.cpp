#include "hamming_network.h"
#include <vector>
#include <iostream>

int Hamming::RunNetwork(int input[]) {
	int a[sizeof(weight) / sizeof(*weight)] = { 0, 0 };
	for (int y = 0; y < (sizeof(weight) / sizeof(*weight)); y++) {
		for (int x = 0; x < (sizeof(weight[0]) / sizeof(*weight[0])); x++) {
			a[y] += input[x] * weight[y][x];
		}
		a[y] += bias[y];
		std::cout << a[y] << std::endl;
	}


	return 0;
}