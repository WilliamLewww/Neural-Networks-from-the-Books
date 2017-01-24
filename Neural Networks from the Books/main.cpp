#include "hamming_network.h"
#include <iostream>

Hamming hamming;
int main(int argc, char *argv[]) {
	double input[] = { -1, -1, -1 };
	hamming.Run(input);
	std::cout << hamming.Run(input)[0]; std::cout << ":"; std::cout << hamming.Run(input)[1] << std::endl;
	std::cin.ignore();
}