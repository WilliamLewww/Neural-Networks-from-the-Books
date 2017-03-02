#pragma once
#include "multilayer_perceptron.h"
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
} PerceptronStruct;

void GeneratePerceptronWindow(PerceptronStruct*);
void InitializePerceptron(PerceptronStruct*);
void UpdatePerceptron(double, PerceptronStruct*);