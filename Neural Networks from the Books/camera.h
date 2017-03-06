#pragma once
#include "vector2.h"
#include "input.h"
#include "global.h"

struct Camera {
	Vector2 position;
	Vector2 scale;

	Vector2 RelativeMouse() {
		return Vector2(mouseX - position.x * (SCREENWIDTH / 2), mouseY + position.y * (SCREENHEIGHT / 2));
	}

	Camera(Vector2 pos, float scaleX, float scaleY) {
		position = pos;
		scale = Vector2(scaleX, scaleY);
	}
};

void UpdateCamera(Camera*);