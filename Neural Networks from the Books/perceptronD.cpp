#include "perceptronD.h"

void PerceptronD::Initialize() {
	perceptron.Initialize(0);

	visualiser.SetPerceptron(&perceptron);
	visualiser.Initialize();
}

void PerceptronD::Update(double dTime) {
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

	GenerateWindow();

	timer += dTime;
}

void PerceptronD::GenerateWindow() {
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Test");
	ImGui::Text("Menu");
	ImGui::InputFloat("Step", &tempStep);
	ImGui::InputFloat("Input", &val, 1);
	ImGui::SetNextWindowSizeConstraints(ImVec2(150, 200), ImVec2(150, 200));
	ImGui::SetWindowSize(ImVec2(150, 200));
	if (ImGui::Button("FeedForward")) {
		perceptron.FeedInput(val);
		step = tempStep;
		initial = true;
		std::cout << initial << std::endl;
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