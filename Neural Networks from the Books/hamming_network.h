#pragma once

class Hamming {
	//prototype patterns
	//shape, texture, weight
	int weight[2][3] = {{ 1, -1, -1 },
						{ 1,  1, -1	}};

	//bias = number of elements in input vector
	int bias[2] = { 3, 3 };

public:
	int RunNetwork(int input[]);
};