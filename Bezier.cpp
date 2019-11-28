#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
	for (int i = 0; i < BEZIERSEGMENTS + 1; i++)
	{
		Points[i] = BezierCalculation(float(i) / BEZIERSEGMENTS);
	}
}

// This draws the 4 cubic control points of the bezier.
void Bezier::draw(SDL_Renderer *renderer) const
{
	for (int i = 0; i < BEZIERSEGMENTS; i++)
	{
		SDL_RenderDrawLineF(renderer, Points[i].x, Points[i].y, Points[i + 1].x, Points[i + 1].y);
	}
}

// The equation to get the 4 control points of the curve.
Vector2 Bezier::BezierCalculation(float t)
{
	Vector2 curvePoints = Vector2();
	curvePoints = pow((1.0f - t), 3.0f) * p0 + 3.0f * pow((1.0f - t), 2.0f)*t*p1 + 3.0f * (1.0f - t) * pow(t, 2.0f) * p2 + pow(t, 3.0f) * p3;

	return curvePoints;
}
		

