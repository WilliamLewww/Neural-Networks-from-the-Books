#pragma once
#include <iostream>

class Hopfield {
	//pre-computed for example
	double weight[3][3] = { { 0.2,  0.0, 0.0 },
							{ 0.0,  1.2, 0.0 },
							{ 0.0,  0.0, 0.2 }};

	double bias[3] = { 0.9, 0, -0.9 };

	double* Recurrent(double* input);
	double* satlins(double* input);
public:
	double* Run(double input[]);
};