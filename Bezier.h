#pragma once

#include "Vector2.h"
#include <vector>

// Number of curves to use when creating the bezier i.e. smoothness
#define CURVES 3

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

	static float lineLength() { return 1.0 / CURVES; }

	// Calculate position along bezier curve based on range 0-1
	Vector2 getPosAlongBezier(float t);

	Vector2 getPointAt(int index) 
	{ 
		if (index >= 0 && index <= CURVES + 1) 
			return Vector2(points[index].x, points[index].y); 
		else 
			return Vector2();
	}

	static int curves() { return CURVES; }

private:
	Vector2 p0, p1, p2, p3;

	// Points forming the curve
	SDL_Point points[CURVES + 1];
	SDL_Point pointsOuter[CURVES + 1];

	// Utility function for converting from Vector2 to SDL_Point
	static SDL_Point Vec2toSDLPoint(const Vector2& in)
	{
		SDL_Point out = SDL_Point();

		out.x = in.x;
		out.y = in.y;

		return out;
	}
};
