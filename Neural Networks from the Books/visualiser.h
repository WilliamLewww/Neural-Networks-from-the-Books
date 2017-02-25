#pragma once
#include "multilayer_perceptron_ch11.h"
#include "spritebatch.h"
#include <vector>

class Visualiser {
	std::vector<Circle> circleList;
	PerceptronML* perceptron;
public:
	void SetPerceptron(PerceptronML*);
	void Initialize();
	void Draw();
};