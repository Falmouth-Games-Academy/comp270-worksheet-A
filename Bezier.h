#pragma once

#include "Vector2.h"

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

	Vector2 FindPFinal(float t, Vector2 p) const;

	Vector2 FindTangent(float t, Vector2 tangent) const;

private:
	Vector2 p0, p1, p2, p3;
	int segments = 20;
};