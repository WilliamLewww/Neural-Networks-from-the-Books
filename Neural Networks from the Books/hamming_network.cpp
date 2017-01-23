#include "hamming_network.h"
#include <iostream>

//a1 = purelin(W1p + b1)
//a2(0) = a1
//a2(t+1) = poslin(W2a2(t))
int Hamming::RunNetwork(int input[], int length) {
	for (int z = 0; z < length; z++) {
		std::cout << input[z] << std::endl;
	}
	std::cin.ignore();

	return 0;
}