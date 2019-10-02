#pragma once

#include "Vector2.h"

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

	static int GetPrecision() { return precision; }

	Vector2 GetVectorPosition(float percent);

private:
	const static int precision = 20;
	
	Vector2 p0, p1, p2, p3;

	SDL_Point ConvertVector2(Vector2 vector);
	SDL_Point FindPosition(float percent);
	
	SDL_Point points[precision+1];


};
