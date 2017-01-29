#pragma once
#include <vector>

const double e = 2.71828182845904523536;

class PerceptronML {
	double a0 = 1;

	double w1[2] = { -0.27, -0.41 };
	double w2[2] = { 0.09, -0.17 };

	double b1[2] = { -0.48, -0.13 };
	double b2 = 0.48;

	void FeedForward();
	double logsig(double value);
public:
	void Run();
};