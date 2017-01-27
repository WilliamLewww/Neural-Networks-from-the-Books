#include "perceptron_learning_rule_ch4.h"

double* PerceptronLR::Run() {
	srand(time(0));

	InitializeWeight();
	bool maxLearning = false;

	//std::cout << sizeof(input[0]) / (sizeof(*input[0])) << std::endl;

	int iteration = 0, cycleCount = 0;
	while (maxLearning == false) {
		//std::cout << weight[0] << ":" << weight[1] << std::endl;
		if (FeedForward(iteration)) { cycleCount += 1; }
		else { cycleCount = 0; }

		if (iteration == sizeof(input) / (sizeof(*input)) - 1) { iteration = 0; }
		else { iteration += 1; }

		if (cycleCount == sizeof(input) / (sizeof(*input))) maxLearning = true;
	}

	return weight;
}

bool PerceptronLR::FeedForward(int index) {
	double net = 0;
	for (int x = 0; x < sizeof(input[0]) / (sizeof(*input[0])) - 1; x++) {
		net += weight[x] * input[index][x];
	}
	net = hardlim(net);

	if (net == input[index][sizeof(input[0]) / (sizeof(*input[0])) - 1]) { return true; }

	LearningRule(index, net);
	return false;
}

void PerceptronLR::LearningRule(int index, int value) {
	if (input[index][sizeof(input[0]) / (sizeof(*input[0])) - 1] == 1 && value == 0) {
		for (int x = 0; x < sizeof(input[0]) / (sizeof(*input[0])) - 1; x++) { weight[x] += input[index][x]; }
	}

	if (input[index][sizeof(input[0]) / (sizeof(*input[0])) - 1] == 0 && value == 1) {
		for (int x = 0; x < sizeof(input[0]) / (sizeof(*input[0])) - 1; x++) { weight[x] -= input[index][x]; }
	}
}

int PerceptronLR::hardlim(double value) {
	if (value >= 0) { return 1; }
	return 0;
}

void PerceptronLR::InitializeWeight() {
	for (int x = 0; x < 100; x++) {
		weight[x] = (double)(rand() % 21 - 10) / 10;
	}
}

void PerceptronLR::InitializeInput(std::vector<std::vector<double>> inputParam) {
	for (int x = 0; x < inputParam[0].size(); x++) {
		for (int y = 0; y < inputParam.size(); y++) {
			input[y][x] = inputParam[y][x];
		}
	}

	/*for (int y = 0; y < inputParam.size(); y++) {
		for (int x = 0; x < inputParam[0].size(); x++) {
			std::cout << input[y][x] << ',';
		}
		std::cout << std::endl;
	}*/
}