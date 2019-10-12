#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{

	// set percentage to 0, the start of the bezier curve
	float percent = 0;

	// generate many points for the bezier curve, according to precision
	for (int i = 0; i < precision+2; i++)
	{
		points[i] = FindPosition(percent);

		percent += 1.0 / precision;
	}

	// now we gonna try making this path THICC

	for (int j = 0; j < precision+1; j++)  // OUTER LINE
	{
		int x_dif = points[i+1].x - points[i].x;  
		int y_dif = points[i+1].y - points[i].y;  

		int magnitude = pow(x_dif,2) + pow(y_dif,2); // we will use this as a modifier so keep a constant distance from the line.

		int x_dire = y_dif * (3 / magnitude);
		int y_dire = -x_dif * (3 / magnitude);

		SDL_Point tempPoint = new SDL_Point(x_dire, y_dire);

		outerLine[i] = tempPoint;
	}


}

void Bezier::draw(SDL_Renderer *renderer) const
{
	//SDL_RenderDrawLine();

	for (int i = 0; i < precision; i++)
	{
		SDL_RenderDrawLineF(renderer, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		SDL_RenderDrawLineF(renderer, outerLine[i].x, outerLine[i].y, outerLine[i + 1].x, outerLine[i + 1].y);

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
