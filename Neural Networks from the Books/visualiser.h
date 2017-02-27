#pragma once
#include "multilayer_perceptron_ch11.h"
#include "spritebatch.h"
#include <vector>

class Node {
	double color[3] = { 0, 0, 0 };
public:
	Vector2 position;
	float radius;

	double* value;

	Node(Vector2 posPara, float radiusPara) {
		position = posPara;
		radius = radiusPara;
	}

	Node(Vector2 posPara, float radiusPara, double* valueParam) {
		position = posPara;
		radius = radiusPara;
		value = valueParam;
	}

	void SetValue(double*);
	void SetColor(std::vector<Node>, double);
	void Draw();
};

struct Connection {
	double color[3] = { 0, 0, 0 };
	double* weight;
public:
	Node* nodeA;
	Node* nodeB;

	Vector2 pointA;
	Vector2 pointB;

	Connection(Node* nodeAParam, Node* nodeBParam, double* weightParam) {
		nodeA = nodeAParam;
		nodeB = nodeBParam;

		pointA = nodeA->position;
		pointB = nodeB->position;

		weight = weightParam;
	}

	void SetColor(std::vector<Connection>, double);
	void Draw();
};

class Visualiser {
	std::vector<Node> nodeList;
	std::vector<Connection> connectionList;
	PerceptronML* perceptron;
public:
	bool isLinked = false;

	void SetPerceptron(PerceptronML*);
	void Initialize();
	void LinkNodes();
	void Draw();
};