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
	// Angle of line
	float angle = 0;

	// Generate array of SDL_Point to use in rendering lines
	for (int i = 0; i < CURVES + 1; i++)
	{
		points[i] = Vec2toSDLPoint(getPosAlongBezier(t));
		
		if(i > 0)
			angle = atan2(points[i].y - points[i - 1].y, points[i].x - points[i - 1].x);

		SDL_Log(std::to_string(angle * 180 / M_PI).c_str());

		pointsOuter[i].x = points[i].x * cos(angle) - points[i].y * sin(angle);
		pointsOuter[i].y = points[i].y * cos(angle) + points[i].x * sin(angle);

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
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50);
		SDL_RenderDrawLines(renderer, points, CURVES + 1);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLines(renderer, pointsOuter, CURVES + 1);
	}
}
