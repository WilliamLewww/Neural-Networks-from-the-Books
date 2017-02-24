//#include "multilayer_perceptron_c.h"
//#include <stdio.h>
//
//PerceptronML perceptron;
//int main(int argc, char *argv[]) {
//	double input = 0;
//	perceptronML_init(&perceptron, 0);
//
//	while (1) {
//		scanf_s("%lf", &input);
//
//		perceptronML_feedInput(&perceptron, input);
//		while (perceptron.error > 0.001 || perceptron.error < -0.001) {
//			perceptronML_run(&perceptron);
//		}
//	}
//
//	getchar();
//}