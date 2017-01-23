#pragma once

//a1 = purelin(W1p + b1)
//a2(0) = a1
//a2(t+1) = poslin(W2a2(t))
class Hamming {
	//prototype patterns
	//shape, texture, weight
	int weight[2][3] = {{ 1, -1, -1 },
						{ 1,  1, -1	}};

	//bias = number of elements in input vector
	int bias[2] = { 3, 3 };

public:
	int RunNetwork(int input[], int length);
};