#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "perceptron_struct.h"

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