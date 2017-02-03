#include "multilayer_perceptron_ch11.h"

void PerceptronML::GenerateWeightBias(int input, int output) {
	std::vector<std::vector<double>> tempWeight;
	std::vector<double> row;
	for (int y = 0; y < output; y++) {
		for (int x = 0; x < input; x++) {
			row.push_back((double)(rand() % 210 - 100) / 100);
		}

		tempWeight.push_back(row);
	}

	std::vector<double> tempBias;
	for (int x = 0; x < output; x++) {
		tempBias.push_back((double)(rand() % 210 - 100) / 100);
	}

	w.push_back(tempWeight);
	b.push_back(tempBias);
}

void PerceptronML::FeedInput(double input) {
	a0 = { { input } };
	error = 1;
}

void PerceptronML::Initialize(double input) {
	srand(time(0));

	a0 = { { input } };
	GenerateWeightBias(1, 2);
	GenerateWeightBias(2, 1);

	error = 1;
}

double PerceptronML::Calculate(double input) {
	std::vector<std::vector<std::vector<double>>> a;
	std::vector<std::vector<double>> tempA;
	for (int x = 0; x < w.size(); x++) {
		if (x == 0) {
			tempA = FeedForward(a0, w[x], b[x], 1);
		}
		else {
			tempA = FeedForward(a[x - 1], w[x], b[x], 0);
		}
		a.push_back(tempA);
	}

	error = OriginalFunction(a0[0][0]) - a[a.size() - 1][0][0];
	std::cout << error << "||" << a[a.size() - 1][0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;

	return a[a.size() - 1][0][0];
}

void PerceptronML::Run() {
	std::vector<std::vector<std::vector<double>>> a;

	std::vector<std::vector<double>> tempA;
	for (int x = 0; x < w.size(); x++) {
		if (x == 0) {
			tempA = FeedForward(a0, w[x], b[x], 1);
		}
		else {
			tempA = FeedForward(a[x - 1], w[x], b[x], 0);
		}
		a.push_back(tempA);
	}

	std::reverse(a.begin(), a.end());
	a.push_back(a0);
	std::reverse(a.begin(), a.end());

	error = OriginalFunction(a0[0][0]) - a[a.size() - 1][0][0];
	Backpropagation(error, a);

	//std::cout << floor(error * 10000 + 0.5) / 10000 << std::endl;
	std::cout << error << "||" << a[a.size() - 1][0][0] << ":" << OriginalFunction(a0[0][0]) << std::endl;
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

void PerceptronML::Backpropagation(double error, std::vector<std::vector<std::vector<double>>> input) {
	std::vector<std::vector<std::vector<double>>> s;
	std::vector<std::vector<double>> initial;

	for (int x = input.size() - 2; x >= 0; x--) {
		if (x == input.size() - 2) {
			initial = { { -2 * DActivation(0, input[input.size() - 1][0][0]) * error } };
			s.push_back(initial);
		}
		else {
			s.push_back(MultMatrix(GenMatrix(input[x], 1), MultMatrix(s[(input.size() - 3) - x], w[x + 1])));
		}
	}

	std::reverse(s.begin(), s.end());

	for (int y = 0; y < w.size(); y++) {
		for (int x = 0; x < GetLargestMat(w[y]); x++) {
			*GetMatLin(x, w[y]) = *GetMatLin(x, w[y]) - (learningRate * (*GetMatLin(x, s[y])));
		}
	}

	for (int y = 0; y < b.size(); y++) {
		for (int x = 0; x < b[y].size(); x++) {
			b[y][x] = b[y][x] - (learningRate * (*GetMatLin(x, s[y])));
		}
	}

	//sN = fN(nN)(wN + 1)(sN + 1)

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

std::vector<std::vector<double>> PerceptronML::GenMatrix(std::vector<std::vector<double>> input, int function) {
	std::vector<std::vector<double>> output;
	std::vector<double> row;

	int layer = 0;

	if (input.size() > input[0].size()) {
		layer = 1;
	}

	for (int x = 0; x < input.size(); x++) {
		for (int y = 0; y < input.size(); y++) {
			if (y == x) {
				if (layer == 1) {
					row.push_back(DActivation(function, input[x][0]));
				}
				else {
					row.push_back(DActivation(function, input[0][x]));
				}
			}
			else {
				row.push_back(0.0);
			}
		}

		output.push_back(row);
	}

	return output;
}

std::vector<std::vector<double>> PerceptronML::MultMatrix(std::vector<std::vector<double>> matB, std::vector<std::vector<double>> matA) {
	std::vector<std::vector<double>> product;
	std::vector<double> row;

	double total = 0;;
	for (int y = 0; y < matB.size(); y++) {
		for (int x = 0; x < matA[0].size(); x++) {
			for (int inner = 0; inner < matB[0].size(); inner++) {
				total += matB[y][inner] * matA[inner][x];
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

	double total = 0;;
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