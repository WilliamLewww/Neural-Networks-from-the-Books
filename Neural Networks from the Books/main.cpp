#include "hamming_network.h"
#include "hopfield_network.h"
#include <iostream>

Hamming hamming;
Hopfield hopfield;
int main(int argc, char *argv[]) {
	double input[] = { -1, -1, -1 };
	hopfield.Run(input);
	//std::cout << hamming.Run(input)[0]; std::cout << ":"; std::cout << hamming.Run(input)[1] << std::endl;
	std::cin.ignore();
}