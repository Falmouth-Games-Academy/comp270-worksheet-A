#pragma once

#include "Vector2.h"

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

	Vector2 GetBezierCurvePoint(float t) const;
	void BezierCurve(SDL_Renderer* renderer) const;

private:
	Vector2 p0, p1, p2, p3;
	SDL_Renderer* renderer = nullptr;
	const int static SEGMENTS = 20;
	Vector2 point[SEGMENTS + 1];
};
