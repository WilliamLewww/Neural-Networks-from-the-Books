#pragma once
#include "multilayer_perceptron.h"
#include "visualiser.h"

class PerceptronClass {
public:
	PerceptronML perceptron;
	Visualiser visualiser;

	std::string name;

	PerceptronClass(std::string namePara) { name = namePara; }
	PerceptronClass(std::string namePara, Vector2 pos) { name = namePara; visualiser.SetPosition(pos); }

	bool initial = false;
	bool radio = false, rise = true;
	int iteration = 0;
	float val = 0, step = 50, tempStep = 50;

	int timer = 0;

	void GeneratePerceptronWindow();
	void InitializePerceptron();
	void InitializePerceptron(std::vector<int>);
	void UpdatePerceptron(double);
};

typedef struct PerceptronStruct {
	PerceptronML perceptron;
	Visualiser visualiser;

	std::string name;

	PerceptronStruct() {}
	PerceptronStruct(std::string namePara) { name = namePara; }

	bool initial = false;
	bool radio = false, rise = true;
	int iteration = 0;
	float rate = 0.1;
	float val = 0, step = 50, tempStep = 50;

	int timer = 0;
} PerceptronStruct;

void GeneratePerceptronWindow(PerceptronStruct*);
void InitializePerceptron(PerceptronStruct*);
void InitializePerceptron(PerceptronStruct*, std::vector<int>);
void UpdatePerceptron(double, PerceptronStruct*);