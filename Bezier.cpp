#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
	// Assign points to Bezier
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	// Generate curves based on desired smoothness
	float t = 0;

	// Generate array of SDL_Point to use in rendering lines
	for (int i = 0; i < CURVES + 1; i++)
	{
		points[i] = Vec2toSDLPoint(getPosAlongBezier(t));

		t += 1.0 / CURVES;
	}
}

Vector2 Bezier::getPosAlongBezier(float t)
{
	Vector2 pos = Vector2();
	
	pos = (pow((1 - t), 3) * p0 + 3 * pow((1 - t), 2) * t * p1 + 3 * (1 - t) * pow(t, 2) * p2 + pow(t, 3) * p3);

	return pos;
}

void Bezier::draw(SDL_Renderer *renderer) const
{
	for (int i = 0; i < CURVES; i++)
	{
		SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
}
