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

PerceptronLR perceptron;
int main(int argc, char *argv[]) {
	std::vector<std::vector<double>> inputAND = {{ 1, 1, 0 }, { 2, 1, 0 }, { 1, 2, 0 }, { 2, 2, 1 }};
	std::vector<std::vector<double>> inputOR = {{ 1, 1, 0 },{ 2, 1, 1 },{ 1, 2, 1 },{ 2, 2, 1 }};
	perceptron.InitializeInput(inputAND);
	perceptron.Run();

	std::cin.ignore();
}