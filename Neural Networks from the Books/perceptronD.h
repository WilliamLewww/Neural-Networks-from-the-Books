#pragma once
#include "multilayer_perceptron.h"
#include "visualiser.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"

class PerceptronD {
public:
	PerceptronML perceptron;
	Visualiser visualiser;

	const char* name;

	PerceptronD() {
		//name = namePara.c_str();
	}

	bool initial = false;
	bool radio = false, rise = true;
	int iteration = 0;
	float val = 0, step = 50, tempStep = 50;

	int timer = 0;

	void GenerateWindow();
	void Initialize();
	void Update(double);
};