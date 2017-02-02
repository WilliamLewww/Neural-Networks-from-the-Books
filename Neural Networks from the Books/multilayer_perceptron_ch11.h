#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>

#define PI 3.14159265
const double e = 2.71828182845904523536;

class PerceptronML {
	std::vector<std::vector<std::vector<double>>> w;
	std::vector<std::vector<double>> b;

	std::vector<std::vector<double>> a0;

	std::vector<std::vector<double>> GenMatrix(std::vector<double> input, int function);
	std::vector<std::vector<double>> MultMatrix(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight);
	std::vector<std::vector<double>> FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function);

	void Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input);

	double Activation(int function, double value);
	double DActivation(int function, double value);

	double OriginalFunction(double value);
public:
	double error;

	void Run();
	double Calculate(double input);

	void FeedInput(double input);
	void Initialize(double input);

	void GenerateWeightBias(int input, int output);
};