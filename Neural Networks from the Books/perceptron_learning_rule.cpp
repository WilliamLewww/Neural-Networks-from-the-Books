#include "perceptron_learning_rule.h"

double* PerceptronLR::Run() {
	srand(time(0));

	InitializeWeightBias();
	bool maxLearning = false;

	//std::cout << sizeof(input) / (sizeof(*input)) << std::endl;
	int caseCount = input.size();

	//std::cout << weight[0] << ":" << weight[1] << "||" << bias << std::endl;
	int iteration = 0, cycleCount = 0;
	while (maxLearning == false) {
		if (FeedForward(iteration)) { cycleCount += 1; }
		else { cycleCount = 0; }

		//std::cout << weight[0] << ":" << weight[1] << "||" << bias << ":" << iteration << std::endl;

		if (iteration == caseCount - 1) { iteration = 0; }
		else { iteration += 1; }

		if (cycleCount == caseCount) { maxLearning = true; }
	}

	return weight;
}

double PerceptronLR::Calculate(double inputParam[], int length) {
	double net = 0;
	for (int x = 0; x < length; x++) {
		net += weight[x] * inputParam[x];
	}
	net += bias;
	net = hardlim(net);

	return net;
}

bool PerceptronLR::FeedForward(int index) {
	double net = 0;
	for (int x = 0; x < input[0].size() - 1; x++) {
		net += weight[x] * input[index][x];
	}
	net += bias;
	net = hardlim(net);

	//std::cout << net << ":" << input[index][input[0].size() - 1] << std::endl;
	if (net == input[index][input[0].size() - 1]) { return true; }

	LearningRule(index, net);
	return false;
}

void PerceptronLR::LearningRule(int index, int value) {
	if (input[index][input[0].size() - 1] == 1 && value == 0) {
		for (int x = 0; x < input[0].size() - 1; x++) { weight[x] += input[index][x]; }
		bias += value;
	}

	if (input[index][input[0].size() - 1] == 0 && value == 1) {
		for (int x = 0; x < input[0].size() - 1; x++) { weight[x] -= input[index][x]; }
		bias -= value;
	}
}

int PerceptronLR::hardlim(double value) {
	if (value >= 0) { return 1; }
	return 0;
}

void PerceptronLR::InitializeWeightBias() {
	for (int x = 0; x < 100; x++) {
		weight[x] = (double)(rand() % 21 - 10) / 10;
	}

	bias = (double)(rand() % 21 - 10) / 10;
}

void PerceptronLR::InitializeInput(std::vector<std::vector<double>> inputParam) {
	input = inputParam;

	/*for (int y = 0; y < inputParam.size(); y++) {
		for (int x = 0; x < inputParam[0].size(); x++) {
			std::cout << input[y][x] << ',';
		}
		std::cout << std::endl;
	}*/
}