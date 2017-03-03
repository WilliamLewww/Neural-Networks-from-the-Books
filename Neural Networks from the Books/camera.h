#pragma once
#include "vector2.h"
#include "input.h"

struct Camera {
	Vector2 position;
	Vector2 scale;

	Camera(Vector2 pos, float scaleX, float scaleY) {
		position = pos;
		scale = Vector2(scaleX, scaleY);
	}
};

void UpdateCamera(Camera*);