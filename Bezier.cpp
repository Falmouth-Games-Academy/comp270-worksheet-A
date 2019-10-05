#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
}

void Bezier::draw(SDL_Renderer *renderer) const
{
	//Draws the curve
	Vector2 pFinal;
	Vector2 previousPFinal;
	for (float i = 0; i <= segments; i++)
	{
		pFinal = FindPFinal(i / segments, pFinal);
		if (i >= 1)
		{
			SDL_RenderDrawLine(renderer, previousPFinal.x, previousPFinal.y, pFinal.x, pFinal.y);
		}
		previousPFinal = pFinal;
	}
}

Vector2 Bezier::FindPFinal(float t, Vector2 point) const
{
	//Applies the formula to find the current curve point relative to t
	point.x = pow(1-t, 3) * p0.x + 3 * pow(1 - t, 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
	point.y = pow(1 - t, 3) * p0.y + 3 * pow(1 - t, 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
	return point;
}
