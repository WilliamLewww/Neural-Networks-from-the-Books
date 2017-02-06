#ifndef MULTILAYER_PERCEPTRON_C
#define MULTILAYER_PERCEPTRON_C

#define PI 3.14159265
#define e = 2.71828182845904523536;

typedef struct PerceptronML {
	double learningRate;
	double*** w;
	double** b;
	double a0[1][1];

} PerceptronML;

void perceptronML_feedInput(PerceptronML*, double);
void perceptronML_init(PerceptronML*, double);
void perceptronML_generateWeightBias(double**, double*, int, int);

#endif