#include "camera.h"

void UpdateCamera(Camera* camera) {
	if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) { 
		camera->position.x -= 0.001;
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) {
		camera->position.x += 0.001;
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_w) != keyList.end()) {
		camera->position.y -= 0.001;
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_s) != keyList.end()) {
		camera->position.y += 0.001;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_q) != keyList.end()) {
		camera->scale.x -= 0.005;
		camera->scale.y -= 0.005;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_e) != keyList.end()) {
		camera->scale.x += 0.005;
		camera->scale.y += 0.005;
	}
}