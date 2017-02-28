#include "visualiser.h"

void Node::Draw() {
	DrawCircle(position, radius, color);
	DrawCircle(position, radius - 0.5, color);
	DrawCircle(position, radius - 1, color);
}

void Node::SetValue(double* val) {
	value = val;
}

void Node::SetColor(std::vector<Node> nL, double value) {
	double max = *nL[0].value;

	for (int x = 1; x < nL.size(); x++) {
		if (*nL[x].value > max) { max = *nL[x].value; }
	}

	color[0] = ConvertColor((value / max) * 255);
	color[1] = ConvertColor((1 - (value / max)) * 255);
	color[2] = 0;

	/*if (value > 0) {
		color[0] = ConvertColor(0);
		color[1] = ConvertColor(255);
		color[2] = 0;
	}
	else {
		color[0] = ConvertColor(255);
		color[1] = ConvertColor(0);
		color[2] = 0;
	}*/
}

void Connection::SetWeight(double* weightPara) {
	weight = weightPara;
}

void Connection::Draw() {
	DrawLine(pointA, pointB, color);
	DrawLine(pointA - Vector2(0, 1), pointB - Vector2(0, 1), color);
	DrawLine(pointA + Vector2(0, 1), pointB + Vector2(0, 1), color);
}

void Connection::SetColor(std::vector<Connection> cL, double value) {
	double max = *cL[0].weight;

	for (int x = 1; x < cL.size(); x++) {
		if (*cL[x].weight > max) { max = *cL[x].weight; }
	}

	//std::cout << value / max << std::endl;
	color[0] = ConvertColor((value / max) * 255);
	color[1] = ConvertColor((1 - (value / max)) * 255);
	color[2] = (color[0] + color[1] / 2);

	/*if (value > 0) {
		color[0] = ConvertColor(0);
		color[1] = ConvertColor(255);
		color[2] = 0;
	}
	else {
		color[0] = ConvertColor(255);
		color[1] = ConvertColor(0);
		color[2] = 0;
	}*/
}

void Visualiser::SetPerceptron(PerceptronML* perceptronParam) {
	perceptron = perceptronParam;
}

void Visualiser::Initialize() {
	std::vector<Node> tempNodeList;
	std::vector<Node> tempNodeList2;
	nodeList.push_back(Node(Vector2(100, (SCREENHEIGHT / 4) * 2), 25));
	tempNodeList.push_back(nodeList[0]);

	for (int x = 0; x < perceptron->b.size(); x++) {
		for (int y = 0; y < perceptron->b[x].size(); y++) {
			nodeList.push_back(Node(Vector2((SCREENWIDTH / (perceptron->b.size() + 1)) * (x + 1) + 100, (y + 1) * ((SCREENHEIGHT / 2) / (perceptron->b[x].size() + 1)) + (SCREENHEIGHT / 4)), 25));
			tempNodeList2.push_back(nodeList[nodeList.size() - 1]);
		}

		for (int y = 0; y < perceptron->b[x].size(); y++) {
			for (int z = 0; z < tempNodeList.size(); z++) {
				connectionList.push_back(Connection(&tempNodeList[z], &nodeList[nodeList.size() - y - 1], &perceptron->w[x][y][z]));
			}
		}

		tempNodeList.clear();
		tempNodeList = tempNodeList2;
		tempNodeList2.clear();
	}
}

void Visualiser::RelinkConnection() {
	int iteration = 0;
	for (int x = 0; x < perceptron->w.size(); x++) {
		for (int y = 0; y < perceptron->w[x].size(); y++) {
			for (int z = 0; z < perceptron->w[x][y].size(); z++) {
				connectionList[iteration].SetWeight(&perceptron->w[x][y][z]);
				iteration += 1;
			}
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

void Visualiser::Draw() {
	for (Node node : nodeList) {
		if (isLinked) {
			node.SetColor(nodeList, *node.value);
		}
		node.Draw();
	}

	for (Connection connection : connectionList) {
		connection.SetColor(connectionList, *connection.weight);
		connection.Draw();
	}
}