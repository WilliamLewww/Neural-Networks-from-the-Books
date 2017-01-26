#include "hamming_network_ch3.h"
#include "hopfield_network_ch3.h"
#include "perceptron_network_ch3.h"
#include "perceptron_learning_rule_ch4.h"
#include <iostream>

///CHAPTER 3
//Hamming hamming;
//Hopfield hopfield;
//Perceptron perceptron;
//int main(int argc, char *argv[]) {
//	double input[] = { 1, 1, 1 };
//	hamming.Run(input);
//	std::cout << hamming.Run(input)[0]; std::cout << ":"; std::cout << hamming.Run(input)[1] << std::endl;
//
//	hopfield.Run(input);
//	std::cout << hopfield.Run(input)[0]; std::cout << ":"; std::cout << hopfield.Run(input)[1]; std::cout << ":"; std::cout << hopfield.Run(input)[2] << std::endl;
//
//	std::cout << perceptron.Run(input) << std::endl;
//
//	std::cin.ignore();
//}

PerceptronAND perceptron;
int main(int argc, char *argv[]) {
	perceptron.Run();

	std::cin.ignore();
}