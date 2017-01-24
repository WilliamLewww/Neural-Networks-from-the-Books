#pragma once
#include <vector>
#include <iostream>

class Hamming {
	//prototype patterns
	//shape, texture, weight
	double weight[2][3] = {{ 1, -1, -1 },
						{ 1,  1, -1	}};

	//any number less than 1
	double weightRec[2][2] = { { 1.0, -0.5},
							   {-0.5,  1.0}};

	//bias = number of elements in input vector
	double bias[2] = { 3, 3 };

	double* FeedForward(double* input);
	double* Recurrent(double* input);
public:
	double* Run(double input[]);
};