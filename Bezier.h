#pragma once

#include "Vector2.h"

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

	float getCurrentSegmentLength(Vector2 carPos, SDL_Renderer *renderer) const;

	Vector2 findCurvePoint(float t, Vector2 p) const;

	Vector2 findCurveTangent(float t, Vector2 tangent) const;

private:
	Vector2 p0, p1, p2, p3;
	const int segments = 20;
	const int approximateSegments = 1000;
};

float distance(Vector2 a, Vector2 b);