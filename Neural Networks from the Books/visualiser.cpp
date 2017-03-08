#include "visualiser.h"

void Node::Draw(Vector2 visPos) {
	DrawCircle(position.Get() + visPos.Get(), radius, color);
	DrawCircle(position.Get() + visPos.Get(), radius - 0.5, color);
	DrawCircle(position.Get() + visPos.Get(), radius - 1, color);
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

void Connection::Draw(Vector2 visPos) {
	DrawLine((pointA->Get() + visPos.Get()), (pointB->Get() + visPos.Get()), color);
	DrawLine((pointA->Get() + visPos.Get()) - Vector2(0, 1), (pointB->Get() + visPos.Get()) - Vector2(0, 1), color);
	DrawLine((pointA->Get() + visPos.Get()) + Vector2(0, 1), (pointB->Get() + visPos.Get()) + Vector2(0, 1), color);
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
	nodeList.push_back(Node(Vector2(100, (SCREENHEIGHT / 4) * 2), 25));

	for (int x = 0; x < perceptron->b.size(); x++) {
		for (int y = 0; y < perceptron->b[x].size(); y++) {
			nodeList.push_back(Node(Vector2((SCREENWIDTH / (perceptron->b.size() + 1)) * (x + 1) + 100, (y + 1) * ((SCREENHEIGHT / 2) / (perceptron->b[x].size() + 1)) + (SCREENHEIGHT / 4)), 25));
		}
	}

	int lowestIndex = 1, highestIndex = 1;
	for (int x = 0; x < perceptron->b.size(); x++) {
		if (x == 0) {
			for (int y = 0; y < perceptron->b[x].size(); y++) {
				connectionList.push_back(Connection(&nodeList[0], &nodeList[highestIndex + y]));
			}
		}
		else {
			highestIndex += perceptron->b[x - 1].size();
			for (int y = 0; y < perceptron->b[x - 1].size(); y++) {
				for (int z = 0; z < perceptron->b[x].size(); z++) {
					connectionList.push_back(Connection(&nodeList[lowestIndex + y], &nodeList[highestIndex + z]));
				}
			}
			lowestIndex += perceptron->b[x - 1].size();
		}
	}

	RelinkConnection();
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

void Visualiser::SetPosition(Vector2 pos) {
	for (Node& node : nodeList) {
		node.position += pos.Get();
	}
}

void Visualiser::SetPositionRelScreen(Vector2 pos) {
	for (Node& node : nodeList) {
		node.position += pos.Get() - Vector2(SCREENWIDTH / 2 - 8, SCREENHEIGHT / 2);
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
		node.Draw(position);
	}

	for (Connection connection : connectionList) {
		connection.SetColor(connectionList, *connection.weight);
		connection.Draw(position);
	}
}