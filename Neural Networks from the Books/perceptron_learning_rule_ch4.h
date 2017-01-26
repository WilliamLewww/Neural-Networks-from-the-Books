#pragma once
#include <stdlib.h>
#include <iostream>

class PerceptronAND {
	double input[4][3] = { { 0, 0, 0 },
	{ 0, 1, 0 },
	{ 1, 0, 0 },
	{ 1, 1, 1 } };

	double weight[2] = {};

	void InitializeWeight();
public:
	double Run();
};