#include "multilayer_perceptron.h"

void PerceptronML::GenerateWeightBias(int input, int output) {
	std::vector<std::vector<double>> tempWeight;
	std::vector<double> row;
	for (int y = 0; y < output; y++) {
		for (int x = 0; x < input; x++) {
			//row.push_back(0.0);
			row.push_back((double)(rand() % 210 - 100) / 100);
		}

		tempWeight.push_back(row);
		row.clear();
	}

	std::vector<double> tempBias;
	for (int x = 0; x < output; x++) {
		//tempBias.push_back(0.0);
		tempBias.push_back((double)(rand() % 210 - 100) / 100);
	}

	w.push_back(tempWeight);
	b.push_back(tempBias);
}

void PerceptronML::FeedInput(double input) {
	a0 = { { input } };
	error = 1;
}

void PerceptronML::FeedLearningRate(double rate) {
	learningRate = rate;
}

void PerceptronML::Initialize(double input, std::vector<int> weightBias) {
	srand(time(0));

	w.clear();
	b.clear();
	a0 = { { input } };

	if (weightBias.size() == 1) {
		GenerateWeightBias(1, weightBias[0]);
		GenerateWeightBias(weightBias[0], 1);
	}
	else {
		for (int x = 0; x < weightBias.size(); x++) {
			if (x == 0) {
				GenerateWeightBias(1, weightBias[x]);
			}
			else {
				if (x == weightBias.size() - 1) {
					GenerateWeightBias(weightBias[x - 1], weightBias[x]);
					GenerateWeightBias(weightBias[x], 1);
				}
				else {
					GenerateWeightBias(weightBias[x - 1], weightBias[x]);
				}
			}
		}
	}

	error = 1;
}

void PerceptronML::Initialize(double input) {
	srand(time(0));

	w.clear();
	b.clear();

	a0 = { { input } };
	GenerateWeightBias(1, 3);
	GenerateWeightBias(3, 2);
	GenerateWeightBias(2, 4);
	GenerateWeightBias(4, 2);
	GenerateWeightBias(2, 1);

	error = 1;
}

double PerceptronML::Calculate(double input) {
	std::vector<std::vector<double>> tempA;

	for (int x = 0; x < w.size(); x++) {
		if (x == 0) {
			tempA = FeedForward(a0, w[x], b[x], 1);
		}
		else {
			tempA = FeedForward(a[x - 1], w[x], b[x], 1);
		}
		a.push_back(tempA);
	}

	error = OriginalFunction(a0[0][0]) - a[a.size() - 1][0][0];
	std::cout << error << "||" << a[a.size() - 1][0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;

	return a[a.size() - 1][0][0];
}

bool PerceptronML::Run() {
	if (initial == false) {
		std::vector<std::vector<double>> tempA;
		for (int x = 0; x < w.size(); x++) {
			if (x == 0) {
				tempA = FeedForward(a0, w[x], b[x], 1);
			}
			else {
				tempA = FeedForward(a[x - 1], w[x], b[x], 1);
			}
			a.push_back(tempA);
		}

		std::reverse(a.begin(), a.end());
		a.push_back(a0);
		std::reverse(a.begin(), a.end());

		initial = true;
	}
	else {
		for (int x = 0; x < w.size(); x++) {
			if (x == 0) {
				a[x + 1] = FeedForward(a0, w[x], b[x], 1);
			}
			else {
				a[x + 1] = FeedForward(a[x], w[x], b[x], 1);
			}
		}

		a[0] = a0;
	}

	error = OriginalFunction(a0[0][0]) - a[a.size() - 1][0][0];
	Backpropagation(error, a);

	//std::cout << floor(error * 10000 + 0.5) / 10000 << std::endl;
	//std::cout << b[0][0] << ":" <<error << "||" << a[a.size() - 1][0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;
	//std::cout << error << "||" << a[a.size() - 1][0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;

	return (isnormal(error) && !isnan(error));
}

int PerceptronML::GetLargestMat(std::vector<std::vector<double>> mat) {
	if (mat.size() > mat[0].size()) {
		return mat.size();
	}

	return mat[0].size();
}

double* PerceptronML::GetMatLin(int index, std::vector<std::vector<double>>& mat) {
	if (mat.size() > mat[0].size()) { return &mat[index][0]; }
	if (mat.size() < mat[0].size()) { return &mat[0][index]; }

	return &mat[0][0];
}

std::vector<std::vector<double>> PerceptronML::FlipMatrix(std::vector<std::vector<double>> mat) {
	std::vector<std::vector<double>> tempMat;
	std::vector<double> col;

	for (int x = 0; x < mat[0].size(); x++) {
		for (int y = 0; y < mat.size(); y++) {
			col.push_back(mat[y][x]);
		}

		tempMat.push_back(col);
		col.clear();
	}

	return tempMat;
}

void PerceptronML::Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input) {
	std::vector<std::vector<std::vector<double>>> s;
	int y = input.size() - 1;
	for (int x = w.size() - 1; x >= 0; x--) {
		if (x == w.size() - 1) {
			s = {{{ -2 * (DActivation(1, input[y][0][0])) * error }}};
		}
		else {
			//std::cout << MultMatrix(GenJacobianMatrix(input[x + 1], 1), MultMatrix(FlipMatrix(w[x + 1]), s[s.size() - 1])).size() << ":" << 
				//MultMatrix(GenJacobianMatrix(input[x + 1], 1), MultMatrix(FlipMatrix(w[x + 1]), s[s.size() - 1]))[0].size() << std::endl;
			s.push_back(MultMatrix(GenJacobianMatrix(input[x + 1], 1), MultMatrix(FlipMatrix(w[x + 1]), s[s.size() - 1])));
		}

		y -= 1;
	}

	std::reverse(s.begin(), s.end());

	for (int y = 0; y < w.size(); y++) {
		for (int x = 0; x < w[y].size(); x++) {
			for (int z = 0; z < w[y][x].size(); z++) {
				w[y][x][z] = w[y][x][z] - (learningRate * (*GetMatLin(x, s[y])));
			}
		}
	}

	for (int y = 0; y < b.size(); y++) {
		for (int x = 0; x < b[y].size(); x++) {
			b[y][x] = b[y][x] - (learningRate * (*GetMatLin(x, s[y])));
		}
	}

	//sN = fN(nN)(wN + 1)(sN + 1)

	//s0 = (-2)F0(n0)(e)
	//s1 = F1(n1)(w2)(s0)
	//s2 = F1(n1)(w3)(s1)

	//s3 = (-2)F3(n3)(e)
	//s2 = F2(n2)(w3)(s3)
	//s1 = F1(n1)(w2)(s2)

	//w3 = w3 - L(s3)(a2)
	//b3 = b3 - L(s3)
	//w2 = w2 - L(s2)(a1)
	//b2 = b2 - L(s2)
	//w1 = w1 - L(s1)(a0)
	//b1 = b1 - L(s1)

	/*std::vector<double> s2 = { -2 * (DActivation(0, input[1][0][0])) * error };
	std::vector<std::vector<double>> f1 = { { DActivation(1, input[0][0][0]), 0 }, { 0, DActivation(1, input[0][1][0]) } };
	std::vector<std::vector<double>> w2new = { { s2[0] * w2[0][0]}, { s2[0] * w2[0][1] } };
	std::vector<std::vector<double>> s1 = MultMatrix(w2new, f1);

	w2[0][0] = w2[0][0] - (0.1 * s2[0] * input[0][0][0]);
	w2[0][1] = w2[0][1] - (0.1 * s2[0] * input[0][1][0]);
	b2[0] = b2[0] - (0.1 * s2[0]);

	w1[0][0] = w1[0][0] - (0.1 * s1[0][0] * a0[0][0]);
	w1[1][0] = w1[1][0] - (0.1 * s1[1][0] * a0[0][0]);
	b1[0] = b1[0] - (0.1 * s1[0][0]);
	b1[1] = b1[1] - (0.1 * s1[1][0]);*/
}

std::vector<std::vector<double>> PerceptronML::GenJacobianMatrix(std::vector<std::vector<double>> input, int function) {
	std::vector<std::vector<double>> output;
	std::vector<double> row;

	int layer = 0;

	if (input.size() > input[0].size()) {
		layer = 1;
	}

	if (layer == 1) {
		for (int x = 0; x < input.size(); x++) {
			for (int y = 0; y < input.size(); y++) {
				if (y == x) {
					row.push_back(DActivation(function, input[x][0]));
				}
				else {
					row.push_back(0.0);
				}
			}

			output.push_back(row);
			row.clear();
		}
	}
	else {
		for (int x = 0; x < input[0].size(); x++) {
			for (int y = 0; y < input[0].size(); y++) {
				if (y == x) {
					row.push_back(DActivation(function, input[0][x]));
				}
				else {
					row.push_back(0.0);
				}
			}

			output.push_back(row);
			row.clear();
		}
	}

	return output;
}

std::vector<std::vector<double>> PerceptronML::MultMatrix(std::vector<std::vector<double>> weight, std::vector<std::vector<double>> input) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total = 0;
	for (int y = 0; y < weight.size(); y++) {
		for (int x = 0; x < input[0].size(); x++) {
			for (int inner = 0; inner < weight[0].size(); inner++) {
				total += weight[y][inner] * input[inner][x];
			}
			row.push_back(total);
			total = 0;
		}
		product.push_back(row);
		row.clear();
	}

	return product;
}

std::vector<std::vector<double>> PerceptronML::FeedForward(std::vector<std::vector<double>> input, std::vector<std::vector<double>> weight, std::vector<double> bias, int function) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total = 0;
	for (int y = 0; y < weight.size(); y++) {
		for (int x = 0; x < input[0].size(); x++) {
			for (int inner = 0; inner < weight[0].size(); inner++) {
				total += weight[y][inner] * input[inner][x];
			}

			total = Activation(function, total + bias[y]);
			row.push_back(total);
			total = 0;
		}
		product.push_back(row);
		row.clear();
	}

	return product;
}

double PerceptronML::Activation(int function, double value) {
	switch (function) {
	case 0:
		//Linear
		return value;
	case 1:
		//Log-Sigmoid
		return 1 / (1 + std::pow(e, -value));
	default:
		break;
	}
}

double PerceptronML::DActivation(int function, double value) {
	switch (function) {
	case 0:
		//Linear
		return 1;
	case 1:
		//Log-Sigmoid
		return (1-value)*(value);
	default:
		break;
	}
}

double PerceptronML::OriginalFunction(double value) {
	return 1 + sin((PI / 4) * value);
}