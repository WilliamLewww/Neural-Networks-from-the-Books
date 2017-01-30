#pragma once
#include <vector>
#include <iostream>
#include <math.h>

#define PI 3.14159265
const double e = 2.71828182845904523536;

class PerceptronML {
	std::vector<std::vector<double>> a0;
	std::vector<std::vector<double>> w1;
	std::vector<double> b1;
	std::vector<std::vector<double>> w2;
	std::vector<double> b2;

	std::vector<std::vector<double>> MultMatrix(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight);
	std::vector<std::vector<double>> FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function);

	void Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input);

	double Activation(int function, double value);
	double DActivation(int function, double value);

	double OriginalFunction(double value);
public:
	double error;

	void Run();
	void Initialize();
};