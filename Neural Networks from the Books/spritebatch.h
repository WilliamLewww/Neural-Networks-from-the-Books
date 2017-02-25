#pragma once
#include <SDL_opengl.h>
#include "vector2.h"
#include "global.h"

class Circle {
	double color[3] = { 0, 0, 0 };
public:
	Vector2 position;
	float radius;

	Circle(Vector2 posPara, float radiusPara) {
		position = posPara;
		radius = radiusPara;
	}

	void SetColor(double, double, double);
	void Draw();
};

void DrawRect(Vector2 position, int width, int height);
void DrawRect(Vector2 position, int width, int height, double color[3]);
void DrawLine(Vector2 a, Vector2 b);
void DrawLine(Vector2 a, Vector2 b, double color[3]);
void DrawCircle(Vector2 position, float radius);
void DrawCircle(Vector2 position, float radius, double color[3]);
void DrawTriangle(Vector2 position, int width, int height);
void DrawTriangle(Vector2 position, int width, int height, double angle);