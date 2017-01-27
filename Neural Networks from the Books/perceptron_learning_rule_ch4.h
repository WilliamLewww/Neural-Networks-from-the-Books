#pragma once
#include <stdlib.h>
#include <iostream>
#include <time.h>

class PerceptronAND {
	double input[3][3] = {{  1,  2, 1 },
						  { -1,  2, 0 },
	                      {  0, -1, 0 }};

	double weight[2] = { 1.0, -0.8 };

	void InitializeWeight();
	bool FeedForward(int index);
	void LearningRule(int index, int value);
	int hardlim(double value);
public:
	double* Run();
};