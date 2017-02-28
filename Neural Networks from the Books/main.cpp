#include "hamming_network_ch3.h"
#include "hopfield_network_ch3.h"
#include "perceptron_network_ch3.h"
#include "perceptron_learning_rule_ch4.h"
#include "multilayer_perceptron_ch11.h"
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
#include "spritebatch.h"
#include "visualiser.h"

void RenderWindow(SDL_Window* window, SDL_GLContext context);

PerceptronML perceptron;
Visualiser visualiser;

bool initial = false;
float val = 0, step = 50, tempStep = 50;
int frameStart, frameEnd, deltaTime = 0, timer = 0;
int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
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

    // Setup ImGui binding
    ImGui_ImplSdl_Init(window);

	perceptron.Initialize(0);

	visualiser.SetPerceptron(&perceptron);
	visualiser.Initialize();

    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    // Main loop
    bool done = false;
    while (!done)
    {
		frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSdl_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }
        ImGui_ImplSdl_NewFrame(window);

		if (initial == true) {
			if (perceptron.error > 0.001 || perceptron.error < -0.001) {
				if (timer > step) {
					if (!perceptron.Run()) { perceptron.Initialize(0); visualiser.RelinkConnection(); }
					visualiser.LinkNodes();
					if (visualiser.isLinked == false) { visualiser.isLinked = true; }

					timer = 0;
				}
			}
		}

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        ImGui::Text("Menu");
		ImGui::InputFloat("Step", &tempStep);
		ImGui::InputFloat("Input", &val, 1);
		ImGui::SetWindowSize(ImVec2(150, 200));
		if (ImGui::Button("FeedForward")) { 
			perceptron.FeedInput(val); 
			step = tempStep;
			initial = true;
		}
        ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);

        // Rendering
		RenderWindow(window, glcontext);

		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
		timer += deltaTime;
    }

    // Cleanup
    ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void RenderWindow(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(ConvertColor(69), ConvertColor(177), ConvertColor(237), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	visualiser.Draw();

	ImGui::Render();

	SDL_GL_SwapWindow(window);
}
