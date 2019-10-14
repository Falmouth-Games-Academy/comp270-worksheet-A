#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
	for (int i = 0; i <= SEGMENTS; i++) {
		point[i] = GetBezierCurvePoint(double(i) / SEGMENTS);
	}
}

void Bezier::draw(SDL_Renderer *renderer) const
{
	//TODO
}


Vector2 Bezier::GetBezierCurvePoint(float t) const
{
	Vector2 pFinal = Vector2();
	pFinal.x = pow(1 - t, 3) * p0.x + pow(1 - t, 2) * 3 * t * p1.x + (1 - t) * 3 * t * t * p2.x + t * t * t * p3.x;
	pFinal.y = pow(1 - t, 3) * p0.y + pow(1 - t, 2) * 3 * t * p1.y + (1 - t) * 3 * t * t * p2.y + t * t * t * p3.y;
	return pFinal;
}

void Bezier::BezierCurve(SDL_Renderer* renderer) const
{
	for (int i = 0; i <= SEGMENTS; i++) {
		SDL_RenderDrawLine(renderer, point[i].x, point[i].y, point[i].x + 1, point[i].y + 1);
	}
}

