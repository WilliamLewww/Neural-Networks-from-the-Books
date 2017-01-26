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
	bool FeedForward(int index);
	void LearningRule(int index, int value);
	inline double hardlim(int value) { if (value >= 0) { return 1; } return 0; }
public:
	double* Run();
};