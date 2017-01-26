#include "perceptron_learning_rule_ch4.h"

double* PerceptronAND::Run() {
	//InitializeWeight();
	bool maxLearning = false, cycle = false;

	FeedForward(0);
	std::cout << weight[0] << ":" << weight[1] << std::endl;

	return weight;
}

bool PerceptronAND::FeedForward(int index) {
	double net = 0;
	for (int x = 0; x < 2; x++) {
		net += weight[x] * input[index][x];
	}
	net = hardlim(net);

	if (net == input[index][2]) { return true; }

	LearningRule(index, net);
	return false;
}

void PerceptronAND::LearningRule(int index, int value) {
	if (input[index][2] == 1 && value == 0) {
		for (int x = 0; x < 2; x++) { weight[x] += input[index][x]; }
	}

	if (input[index][2] == 0 && value == 1) {
		for (int x = 0; x < 2; x++) { weight[x] -= input[index][x]; }
	}
}

void PerceptronAND::InitializeWeight() {
	for (int x = 0; x < 100; x++) {
		weight[x] = (double)(rand() % 21 - 10) / 10;
	}
}