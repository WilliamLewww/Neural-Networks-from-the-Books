#include "perceptron_learning_rule_ch4.h"

double* PerceptronAND::Run() {
	srand(time(0));

	InitializeWeight();
	bool maxLearning = false;

	int iteration = 0, cycleCount = 0;
	while (maxLearning == false) {
		//std::cout << weight[0] << ":" << weight[1] << std::endl;
		if (FeedForward(iteration)) { cycleCount += 1; }
		else { cycleCount = 0; }

		if (iteration == 2) { iteration = 0; }
		else { iteration += 1; }

		if (cycleCount == 3) maxLearning = true;
	}

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

int PerceptronAND::hardlim(double value) {
	if (value >= 0) { return 1; }
	return 0;
}

void PerceptronAND::InitializeWeight() {
	for (int x = 0; x < 100; x++) {
		weight[x] = (double)(rand() % 21 - 10) / 10;
	}
}