#include "hamming_network_ch3.h"
#include "hopfield_network_ch3.h"
#include "perceptron_network_ch3.h"
#include "perceptron_learning_rule_ch4.h"
#include "multilayer_perceptron_ch11.h"
#include "global.h"
#include <math.h>
#include <iostream>

///CHAPTER 3
//Hamming hamming;
//Hopfield hopfield;
//Perceptron perceptron;
//int main(int argc, char *argv[]) {
//	double input[] = { 1, 1, 1 };
//	hamming.Run(input);
//	std::cout << hamming.Run(input)[0]; std::cout << ":"; std::cout << hamming.Run(input)[1] << std::endl;
//
//	hopfield.Run(input);
//	std::cout << hopfield.Run(input)[0]; std::cout << ":"; std::cout << hopfield.Run(input)[1]; std::cout << ":"; std::cout << hopfield.Run(input)[2] << std::endl;
//
//	std::cout << perceptron.Run(input) << std::endl;
//
//	std::cin.ignore();
//}

///CHAPTER 4
//PerceptronLR perceptron;
//int main(int argc, char *argv[]) {
//	//single-neuron cases
//	std::vector<std::vector<double>> inputAND = {{ 0, 0, 0 },{ 1, 0, 0 },{ 0, 1, 0 },{ 1, 1, 1 }};
//	std::vector<std::vector<double>> inputOR = {{ 0, 0, 0 },{ 1, 0, 1 },{ 0, 1, 1 },{ 1, 1, 1 }};
//	std::vector<std::vector<double>> inputNOT = {{ 0, 1 },{ 1, 0 }};
//
//	std::vector<std::vector<double>> inputXOR = { { 0, 0, 0 },{ 0, 1, 1 },{ 1, 0, 1 },{ 1, 1, 0 } };
//	std::vector<std::vector<double>> inputNAND = { { 0, 0, 1 },{ 0, 1, 1 },{ 1, 0, 1 },{ 1, 1, 0 } };
//	
//	//multiple-neuron cases
//	//std::vector<std::vector<double>> inputNOR = {{ 0, 0, 1 },{ 0, 1, 0 },{ 1, 0, 0 },{ 1, 1, 0 }};
//	//std::vector<std::vector<double>> inputXNOR = {{ 0, 0, 1 },{ 0, 1, 0 },{ 1, 0, 0 },{ 1, 1, 1 }};
//	
//	perceptron.InitializeInput(inputAND);
//	perceptron.Run();
//
//	double testInput[2] = {1, 1};
//	std::cout << perceptron.Calculate(testInput, 2) << std::endl;
//
//	std::cin.ignore();
//}

///CHAPTER 11 
//PerceptronML perceptron;
//int main(int argc, char *argv[]) {
//	double input;
//	perceptron.Initialize(0);
//
//	while (true) {
//		std::cin >> input;
//
//		perceptron.FeedInput(input);
//		while (perceptron.error > 0.001 || perceptron.error < -0.001) {
//			if (!perceptron.Run()) {
//				perceptron.Initialize(0);
//			}
//		}
//	}
//
//	std::cin.ignore();
//}

#include <SDL.h>
#include <SDL_opengl.h>
#include "spritebatch.h"
#include "visualiser.h"

void Render(SDL_Window* window, SDL_GLContext context);

SDL_Event event;
SDL_GLContext context;
static SDL_Window* displayWindow;

PerceptronML perceptron;
Visualiser visualiser;
int frameStart, frameEnd, deltaTime = 0, timer = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Net Visualiser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	double input;
	perceptron.Initialize(0);

	visualiser.SetPerceptron(&perceptron);
	visualiser.Initialize();

	Render(displayWindow, context);

	while (true) {
		std::cin >> input;

		perceptron.FeedInput(input);
		while (perceptron.error > 0.001 || perceptron.error < -0.001) {
			frameStart = SDL_GetTicks();

			if (timer > 100) {
				Render(displayWindow, context);
				if (!perceptron.Run()) {
					perceptron.Initialize(0);
				}
				timer = 0.0;
			}

			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
			timer += deltaTime;
		}
	}

	return 0;
}

void Render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(ConvertColor(69), ConvertColor(177), ConvertColor(237), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	visualiser.Draw();

	SDL_GL_SwapWindow(window);
}

float ConvertColor(int rgbValue) {
	return (float)rgbValue / 255;
}