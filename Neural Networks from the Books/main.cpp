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

typedef struct PerceptronStruct {
	PerceptronML perceptron;
	Visualiser visualiser;

	std::string name;

	PerceptronStruct(std::string namePara) { name = namePara; }
	PerceptronStruct(std::string namePara, Vector2 pos) { name = namePara; visualiser.SetPosition(pos); }

	bool initial = false;
	bool radio = false, rise = true;
	int iteration = 0;
	float val = 0, step = 50, tempStep = 50;

	int timer = 0;
}PerceptronStruct;

void GeneratePerceptronWindow(PerceptronStruct*);
void InitializePerceptron(PerceptronStruct*);
void UpdatePerceptron(double, PerceptronStruct*);
void RenderWindow(SDL_Window*, SDL_GLContext, std::vector<PerceptronStruct>);

std::vector<PerceptronStruct> perceptronList;

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

void InitializePerceptron(PerceptronStruct* ps) {
	ps->perceptron.Initialize(0);

	ps->visualiser.SetPerceptron(&ps->perceptron);
	ps->visualiser.LinkNodes();
	ps->visualiser.Initialize();
}

void UpdatePerceptron(double dTime, PerceptronStruct* ps) {
	if (ps->initial == true) {
		if (ps->radio == true) {
			ps->step = ps->tempStep;
		}

		if (ps->perceptron.error > 0.001 || ps->perceptron.error < -0.001) {
			if (ps->timer > ps->step) {
				if (!ps->perceptron.Run()) { ps->perceptron.Initialize(0); ps->visualiser.RelinkConnection(); }
				ps->visualiser.LinkNodes();
				if (ps->visualiser.isLinked == false) { ps->visualiser.isLinked = true; }

				ps->timer = 0;
			}
		}
		else {
			if (ps->radio == true) {
				ps->perceptron.FeedInput(ps->iteration);
				if (ps->iteration > 100) { ps->rise = false; }
				if (ps->iteration < 0) { ps->rise = true; }
				if (ps->rise == true) {
					ps->iteration += 1;
				}
				else {
					ps->iteration -= 1;
				}
			}
		}
	}

	GeneratePerceptronWindow(ps);

	ps->timer += dTime;
}

void GeneratePerceptronWindow(PerceptronStruct* ps) {
	ImGui::SetNextWindowSize(ImVec2(150, 200), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(("Network #" + ps->name).c_str());
	ImGui::Text("Perceptron Menu");
	ImGui::InputFloat("Delay", &ps->tempStep);
	ImGui::InputFloat("Input", &ps->val, 1);
	ImGui::SetNextWindowSizeConstraints(ImVec2(150, 200), ImVec2(150, 200));
	ImGui::SetWindowSize(ImVec2(150, 200));
	if (ImGui::Button("FeedForward")) {
		ps->perceptron.FeedInput(ps->val);
		ps->step = ps->tempStep;
		ps->initial = true;
	}
	if (ImGui::Button("Toggle Range")) {
		ps->perceptron.FeedInput(ps->iteration);
		ps->step = ps->tempStep;
		ps->radio = !ps->radio;
		ps->initial = true;
	}
	ImGui::Text("(%1f -> Error)", ps->perceptron.error);
	ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
	ImGui::End();
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
