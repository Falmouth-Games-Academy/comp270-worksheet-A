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

	calculatePoints();
}

void Bezier::calculatePoints()
{
	// Generate curves based on desired smoothness
	float t = 0;
	// Angle of line
	float angle = 0;

	// Generate array of SDL_Point to use in rendering lines
	for (int i = 0; i < CURVES + 1; i++)
	{
		points[i] = Vec2toSDLPoint(getPosAlongBezier(t));

		// Calculate the 
		if (i > 0)
		{
			// Calculate angles for all but the first line of the curve
			angle = atan2(points[i].y - points[i - 1].y, points[i].x - points[i - 1].x);

			// Calculate corresponding outer and inner points, offset by half of the curve width each
			pointsOuter[i].x = (WIDTH / 2) * sin(angle) + points[i].x;
			pointsOuter[i].y = -(WIDTH / 2) * cos(angle) + points[i].y;
			pointsInner[i].x = -(WIDTH / 2) * sin(angle) + points[i].x;
			pointsInner[i].y = (WIDTH / 2) * cos(angle) + points[i].y;
		}

		t += 1.0 / CURVES;
	}

	// Calculate the angle for the first line of the curve
	angle = atan2(points[1].y - points[0].y, points[1].x - points[0].x);

	// Calculate the first inner and outer points of the track
	pointsOuter[0].x = (WIDTH / 2) * sin(angle) + points[0].x;
	pointsOuter[0].y = -(WIDTH / 2) * cos(angle) + points[0].y;
	pointsInner[0].x = -(WIDTH / 2) * sin(angle) + points[0].x;
	pointsInner[0].y = (WIDTH / 2) * cos(angle) + points[0].y;
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
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLines(renderer, points, CURVES + 1);
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50);
		SDL_RenderDrawLines(renderer, pointsOuter, CURVES + 1);
		SDL_RenderDrawLines(renderer, pointsInner, CURVES + 1);
	}
}
