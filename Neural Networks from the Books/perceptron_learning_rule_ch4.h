#pragma once
#include <stdlib.h>
#include <iostream>

class PerceptronAND {
	double input[3][3] = {{  1,  2, 1 },
						  { -1,  2, 0 },
	                      {  0, -1, 0 }};

	double weight[2] = {1.0, -0.8};

	void InitializeWeight();
	bool FeedForward(int index);
	void LearningRule(int index, int value);
	inline double hardlim(int value) { if (value >= 0) { return 1; } return 0; }
public:
	double* Run();
};