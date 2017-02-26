#include "visualiser.h"

void Node::Draw() {
	DrawCircle(position, radius, color);
}

void Node::SetValue(double* val) {
	value = val;
}

void Node::SetColor(double r, double g, double b) {
	color[0] = ConvertColor(r);
	color[1] = ConvertColor(g);
	color[2] = ConvertColor(b);
}

void Visualiser::SetPerceptron(PerceptronML* perceptronParam) {
	perceptron = perceptronParam;
}

void Visualiser::Initialize() {
	nodeList.push_back(Node(Vector2(100, (SCREENHEIGHT / 4) * 2), 25));

	for (int x = 0; x < perceptron->b.size(); x++) {
		for (int y = 0; y < perceptron->b[x].size(); y++) {
			nodeList.push_back(Node(Vector2((SCREENWIDTH / (perceptron->b.size() + 1)) * (x + 1) + 100, (y + 1) * ((SCREENHEIGHT / 2) / (perceptron->b[x].size() + 1)) + (SCREENHEIGHT / 4)), 25));
		}
	}
}

void Visualiser::LinkNodes() {
	int iteration = 0;
	for (int x = 0; x < perceptron->a.size(); x++) {
		for (int y = 0; y < perceptron->a[x].size(); y++) {
			nodeList[iteration].SetValue(&perceptron->a[x][y][0]);
			iteration += 1;
		}
	}
}

double* GetVisualColor(double value) {
	double color[3];
	color[0] = ConvertColor((1.0 - value) * 255);
	color[1] = ConvertColor(value * 255);
	color[2] = 0;

	return color;
}

void Visualiser::Draw() {
	for (Node node : nodeList) {
		node.Draw();
	}
}