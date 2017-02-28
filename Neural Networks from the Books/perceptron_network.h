#pragma once
#include <iostream>

class Perceptron {
	double weight[1][3] = { 0, 1, 0 };

	double FeedForward(double* input);
	double hardlims(double input);
public:
	double Run(double input[]);
};