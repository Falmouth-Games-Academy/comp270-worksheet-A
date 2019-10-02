#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{

	// set percentage to 0, the start of the bezier curve
	float percent = 0;

	// generate many points for the bezier curver, according to precision

	for (int i = 0; i < precision+1; i++)
	{
		points[i] = FindPosition(percent);

		percent += 1.0 / precision;
	}

}

void Bezier::draw(SDL_Renderer *renderer) const
{
	//SDL_RenderDrawLine();

	for (int i = 0; i < precision; i++)
	{
		SDL_RenderDrawLineF(renderer, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}

}

Vector2 Bezier::GetVectorPosition(float percent)
{
	Vector2 vectorPosition = Vector2();

	vectorPosition = pow((1 - percent), 3)*p0 + 3 * pow((1 - percent), 2)*percent*p1 + 3 * (1 - percent) * pow(percent, 2) * p2 + pow(percent, 3) * p3;

	return vectorPosition;
}

SDL_Point Bezier::ConvertVector2(Vector2 vector)
{
	SDL_Point point = SDL_Point();

	point.x = vector.x;
	point.y = vector.y;

	return point;
}

SDL_Point Bezier::FindPosition(float percent)
{
	Vector2 vectorPosition = Vector2();

	vectorPosition = GetVectorPosition(percent);

	SDL_Point pointPosition = ConvertVector2(vectorPosition);

	return pointPosition;
}
