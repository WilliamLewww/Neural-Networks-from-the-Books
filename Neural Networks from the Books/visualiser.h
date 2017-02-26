#pragma once
#include "multilayer_perceptron_ch11.h"
#include "spritebatch.h"
#include <vector>

double* GetVisualColor(double value);

class Node {
	double color[3] = { 0, 0, 0 };
public:
	Vector2 position;
	float radius;

	double* value;

	Node(Vector2 posPara, float radiusPara, double* valueParam) {
		position = posPara;
		radius = radiusPara;
		value = valueParam;
	}

	void SetColor(double, double, double);
	void Draw();
};

struct Connection {
	Node* nodeA;
	Node* nodeB;

	Vector2 pointA;
	Vector2 pointB;

	Connection(Node* nodeAParam, Node* nodeBParam, double weightParam) {
		nodeA = nodeAParam;
		nodeB = nodeBParam;

		pointA = nodeA->position;
		pointB = nodeB->position;

		weight = weightParam;
	}

	double weight;
};

class Visualiser {
	std::vector<Node> nodeList;
	PerceptronML* perceptron;
public:
	void SetPerceptron(PerceptronML*);
	void Initialize();
	void Draw();
};