#pragma once

#include "Vector2.h"
#include <vector>

// Number of curves to use when creating the bezier i.e. smoothness
#define CURVES 20

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

private:
	Vector2 p0, p1, p2, p3;

	// Points forming the curve
	SDL_Point points[CURVES + 1];

	// Calculate position along bezier curve based on range 0-1
	Vector2 getPosAlongBezier(float t);

	// Utility function for converting from Vector2 to SDL_Point
	static SDL_Point Vec2toSDLPoint(const Vector2& in)
	{
		SDL_Point out = SDL_Point();

		out.x = in.x;
		out.y = in.y;

		return out;
	}
};
