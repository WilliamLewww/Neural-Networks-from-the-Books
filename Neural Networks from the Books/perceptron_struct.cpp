#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "perceptron_struct.h"

void PerceptronClass::InitializePerceptron() {
	perceptron.Initialize(0);

	visualiser.SetPerceptron(&perceptron);
	visualiser.Initialize();
}

void InitializePerceptron(PerceptronStruct* ps) {
	ps->perceptron.Initialize(0);

	ps->visualiser.SetPerceptron(&ps->perceptron);
	ps->visualiser.Initialize();
}

void PerceptronClass::InitializePerceptron(std::vector<int> weightBias) {
	perceptron.Initialize(0, weightBias);

	visualiser.SetPerceptron(&perceptron);
	visualiser.Initialize();
}

void InitializePerceptron(PerceptronStruct* ps, std::vector<int> weightBias) {
	ps->perceptron.Initialize(0, weightBias);

	ps->visualiser.SetPerceptron(&ps->perceptron);
	ps->visualiser.Initialize();
}

void PerceptronClass::UpdatePerceptron(double dTime) {
	if (initial == true) {
		if (radio == true) {
			step = tempStep;
		}

		if (perceptron.error > 0.001 || perceptron.error < -0.001) {
			if (timer > step) {
				if (!perceptron.Run()) { perceptron.Initialize(0); visualiser.RelinkConnection(); }
				visualiser.LinkNodes();
				if (visualiser.isLinked == false) { visualiser.isLinked = true; }

				timer = 0;
			}
		}
		else {
			if (radio == true) {
				perceptron.FeedInput(iteration);
				if (iteration > 100) { rise = false; }
				if (iteration < 0) { rise = true; }
				if (rise == true) {
					iteration += 1;
				}
				else {
					iteration -= 1;
				}
			}
		}
	}

	GeneratePerceptronWindow();

	timer += dTime;
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

void PerceptronClass::GeneratePerceptronWindow() {
	ImGui::Begin(("Network #" + name).c_str());
	ImGui::Text("Perceptron Menu");
	ImGui::InputFloat("Delay", &tempStep);
	ImGui::InputFloat("Input", &val, 1);
	ImGui::SetWindowSize(ImVec2(150, 200));
	if (ImGui::Button("FeedForward")) {
		perceptron.FeedInput(val);
		step = tempStep;
		initial = true;
	}
	if (ImGui::Button("Toggle Range")) {
		perceptron.FeedInput(iteration);
		step = tempStep;
		radio = !radio;
		initial = true;
	}
	ImGui::Text("(%1f -> Error)", perceptron.error);
	ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
	ImGui::End();
}

void GeneratePerceptronWindow(PerceptronStruct* ps) {
	ImGui::Begin(("Network #" + ps->name).c_str());
	ImGui::Text("Perceptron Menu");
	ImGui::InputFloat("Delay", &ps->tempStep);
	ImGui::InputFloat("Input", &ps->val, 1);
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