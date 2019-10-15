#pragma once

#include "Vector2.h"

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;
	Vector2 CalculateBezier(float t);
	float calculateRotation(float t);
private:
	const static int CURVEYSAMPLES = 20;
	Vector2 p0, p1, p2, p3;
	Vector2 incrementalPoints[CURVEYSAMPLES + 1];
};
