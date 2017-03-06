#include "camera.h"

void UpdateCamera(Camera* camera, double deltaTime) {
	double timeS = deltaTime / 1000;
	if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) { camera->position.x -= 1.5 * timeS / camera->scale.x; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) { camera->position.x += 1.5 * timeS / camera->scale.x; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_w) != keyList.end()) { camera->position.y -= 1.5 * timeS / camera->scale.y; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_s) != keyList.end()) { camera->position.y += 1.5 * timeS / camera->scale.y; }

	if (std::find(keyList.begin(), keyList.end(), SDLK_q) != keyList.end()) {
		if (camera->scale.x > 0) {
			camera->scale.x -= 1.0 * timeS;
			camera->scale.y -= 1.0 * timeS;
		}
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_e) != keyList.end()) {
		camera->scale.x += 1.0 * timeS;
		camera->scale.y += 1.0 * timeS;
	}
}