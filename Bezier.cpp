#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
}

void Bezier::draw(SDL_Renderer *renderer) const
{
	// TODO



	for ( int i = 0; i < curveCount; i++ )
	{
		float t = i / curveCount;

		
		Vector2 point = pow( (1 - t), 3 ) * p0 + 3 * pow( (1 - t), 2 ) * t * p1 + 3 * (1 - t) * pow( t, 2 ) * p2 + pow( t, 3 ) * p3;

		float tt = (i + 1) / curveCount;
		Vector2 pointTwo_PointBoogaloo = pow( (1 - tt), 3 ) * p0 + 3 * pow( (1 - tt), 2 ) * tt * p1 + 3 * (1 - tt) * pow( tt, 2 ) * p2 + pow( tt, 3 ) * p3;

		SDL_RenderDrawLine( renderer, point.x, point.y, pointTwo_PointBoogaloo.x, pointTwo_PointBoogaloo.y );


	}









}

