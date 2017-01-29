#include "multilayer_perceptron.h"

void PerceptronML::Run() {

}

void PerceptronML::FeedForward() {

}

double PerceptronML::logsig(double value) {
	return 1 / (1 + std::pow(e, -value));
}