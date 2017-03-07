#pragma once
#include "vector2.h"
#include "input.h"
#include "global.h"

struct Camera {
	Vector2 position;
	Vector2 scale;

	Vector2 RelativeMouse() {
		//(mouseX - position.x * (SCREENWIDTH / 2)), 
		return Vector2(
			(((SCREENWIDTH / 2) + mouseX - SCREENWIDTH) / scale.x) - position.x * (SCREENWIDTH / 2) + SCREENWIDTH / 2,
			(((SCREENHEIGHT / 2) + mouseY - SCREENHEIGHT) / scale.y) + position.y * (SCREENHEIGHT / 2) + SCREENHEIGHT / 2
		);
	}

	Camera(Vector2 pos, float scaleX, float scaleY) {
		position = pos;
		scale = Vector2(scaleX, scaleY);
	}
};

void UpdateCamera(Camera*, double);