#include "visualiser.h"

void Visualiser::SetPerceptron(PerceptronML* perceptronParam) {
	perceptron = perceptronParam;
}

void Visualiser::Initialize() {
	for (int x = 0; x < perceptron->b.size(); x++) {
		for (int y = 0; y < perceptron->b[x].size(); y++) {
			circleList.push_back(Circle(Vector2((SCREENWIDTH / perceptron->b.size()) * x + 100, (y + 1) * ((SCREENHEIGHT / 2) / (perceptron->b[x].size() + 1)) + (SCREENHEIGHT / 4)), 25));
		}
	}
}

void Visualiser::Draw() {
	for (Circle circle : circleList) {
		circle.Draw();
	}
}