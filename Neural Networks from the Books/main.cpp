#include "hamming_network.h"
#include "hopfield_network.h"
#include "perceptron_network.h"
#include "perceptron_learning_rule.h"
#include "multilayer_perceptron.h"
#include "global.h"
#include <math.h>
#include <iostream>

float ConvertColor(int rgbValue) {
	return (float)rgbValue / 255;
}

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

//#include <SDL.h>
//#include <SDL_opengl.h>
//#include "spritebatch.h"
//#include "visualiser.h"
//
//void Render(SDL_Window* window, SDL_GLContext context);
//
//SDL_Event event;
//SDL_GLContext context;
//static SDL_Window* displayWindow;
//
//PerceptronML perceptron;
//Visualiser visualiser;
//int frameStart, frameEnd, deltaTime = 0, timer = 0;
//int main(int argc, char *argv[]) {
//	displayWindow = SDL_CreateWindow("Net Visualiser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
//	context = SDL_GL_CreateContext(displayWindow);
//	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);
//
//	double input;
//	perceptron.Initialize(0);
//
//	visualiser.SetPerceptron(&perceptron);
//	visualiser.Initialize();
//
//	Render(displayWindow, context);
//
//	while (true) {
//		std::cin >> input;
//
//		perceptron.FeedInput(input);
//		while (perceptron.error > 0.001 || perceptron.error < -0.001) {
//			frameStart = SDL_GetTicks();
//
//			if (timer > 50) {
//				Render(displayWindow, context);
//				if (!perceptron.Run()) { perceptron.Initialize(input); visualiser.RelinkConnection(); }
//				visualiser.LinkNodes();
//				if (visualiser.isLinked == false) { visualiser.isLinked = true; }
//
//				timer = 0.0;
//			}
//
//			frameEnd = SDL_GetTicks();
//			deltaTime = frameEnd - frameStart;
//			timer += deltaTime;
//		}
//	}
//
//	return 0;
//}
//
//void Render(SDL_Window* window, SDL_GLContext context) {
//	SDL_GL_MakeCurrent(window, context);
//	glClearColor(ConvertColor(69), ConvertColor(177), ConvertColor(237), 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_PROJECTION);
//
//	visualiser.Draw();
//
//	SDL_GL_SwapWindow(window);
//}
//

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <math.h>
#include "spritebatch.h"
#include "visualiser.h"
#include "perceptron_struct.h"

void RenderWindow(SDL_Window*, SDL_GLContext, std::vector<PerceptronStruct>);

std::vector<PerceptronStruct> perceptronList;

std::vector<const char*> layerList;
std::vector<int> neuronList;
const char** layerListArray;
int currentLayer = 0;

bool showCustomGeneration = false;

bool running = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window *window = SDL_CreateWindow("Net Visualiser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

    ImGui_ImplSdl_Init(window);
    
    while (running) {
		frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSdl_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
				running = true;
        }
        ImGui_ImplSdl_NewFrame(window);

		ImGui::Text("Main Menu");
		if (ImGui::Button("Generate Example")) {
			perceptronList.push_back(PerceptronStruct(std::to_string(perceptronList.size())));
			InitializePerceptron(&perceptronList[perceptronList.size() - 1]);
		}

		if (ImGui::Button("Generate")) {
			showCustomGeneration = !showCustomGeneration;
		}

		if (showCustomGeneration) {
			ImGui::Begin("Custom Network");
			ImGui::SetWindowSize(ImVec2(400, 400));
			if (ImGui::Button("Add Layer")) { 
				layerList.push_back("New Layer"); 
				neuronList.push_back(0);
			}
			if (layerList.size() > 0) { layerListArray = (const char**)&layerList[0];  }
			ImGui::ListBox("", &currentLayer, layerListArray, layerList.size(), 10);
			if (layerList.size() > 0) {
				ImGui::InputInt("# of Neurons", &neuronList[currentLayer], 1);
			}

			if (ImGui::Button("Create")) {
				perceptronList.push_back(PerceptronStruct(std::to_string(perceptronList.size())));
				InitializePerceptron(&perceptronList[perceptronList.size() - 1], neuronList);

				layerList.clear();
				neuronList.clear();
				currentLayer = 0;
				showCustomGeneration = false;
			}
			ImGui::End();
		}

		for (PerceptronStruct &perceptron : perceptronList) { UpdatePerceptron(deltaTime, &perceptron); }
		RenderWindow(window, glcontext, perceptronList);

		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
    }

    ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void RenderWindow(SDL_Window* window, SDL_GLContext context, std::vector<PerceptronStruct> perceptronList) {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(ConvertColor(69), ConvertColor(177), ConvertColor(237), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	for (PerceptronStruct perceptron : perceptronList) {
		perceptron.visualiser.Draw();
	}

	ImGui::Render();

	SDL_GL_SwapWindow(window);
}
