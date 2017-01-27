#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>

class PerceptronLR {
	double input[3][3] = {{  1,  2, 1 },
						  { -1,  2, 0 },
	                      {  0, -1, 0 }};

	double weight[2] = { 1.0, -0.8 };

	double bias;

	void InitializeWeightBias();
	bool FeedForward(int index);
	void LearningRule(int index, int value);
	int hardlim(double value);
public:
	void InitializeInput(std::vector<std::vector<double>> inputParam);
	double* Run();
	double Calculate(double inputParam[], int length);
};