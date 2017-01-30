#pragma once
#include <vector>
#include <iostream>

const double e = 2.71828182845904523536;

class PerceptronML {
	std::vector<std::vector<double>> a0 = {{1}};

	std::vector<std::vector<double>> w1 = { { -0.27 },
											{ -0.41 }};

	std::vector<double> b1 = { -0.48, -0.13 };

	std::vector<std::vector<double>> w2 = {{ 0.09, -0.17 }};
	std::vector<std::vector<double>> b2 = {{ 0.48 }};

	std::vector<std::vector<double>> FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function);
	double Activation(int function, double value);
	double logsig(double value);
public:
	void Run();
};		