#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>

#define PI 3.14159265
const double e = 2.71828182845904523536;

class PerceptronML {
	std::vector<std::vector<double>> FlipMatrix(std::vector<std::vector<double>> mat);
	std::vector<std::vector<double>> GenJacobianMatrix(std::vector<std::vector<double>> input, int function);
	std::vector<std::vector<double>> MultMatrix(std::vector<std::vector<double>> matB, std::vector<std::vector<double>> matA);
	std::vector<std::vector<double>> FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function);

	void Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input);

	double Activation(int function, double value);
	double DActivation(int function, double value);

	double OriginalFunction(double value);

	int GetLargestMat(std::vector<std::vector<double>> mat);
	double* GetMatLin(int index, std::vector<std::vector<double>>& mat);
	bool initial = false;
public:
	double learningRate = 0.1;

	std::vector<std::vector<std::vector<double>>> w;
	std::vector<std::vector<std::vector<double>>> a;
	std::vector<std::vector<double>> b;

	std::vector<std::vector<double>> a0;

	double error;

	bool Run();
	double Calculate(double input);

	void FeedInput(double input);
	void Initialize(double input);
	void Initialize(double input, std::vector<int> weightBias);

	void GenerateWeightBias(int input, int output);
};