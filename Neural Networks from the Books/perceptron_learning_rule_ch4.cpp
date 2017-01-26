#include "perceptron_learning_rule_ch4.h"

double PerceptronAND::Run() {
	InitializeWeight();

	return 0;
}

void PerceptronAND::InitializeWeight() {
	for (int x = 0; x < 100; x++) {
		weight[x] = (double)(rand() % 21 - 10) / 10;
	}
}