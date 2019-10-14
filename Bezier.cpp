#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
}

//Draw a quadratic bezier curve using segments
void Bezier::draw(SDL_Renderer *renderer) const
{
	Vector2 curvePoint;
	Vector2 previousCurvePoint;

	for (float i = 0; i <= segments; i++)
	{
		curvePoint = findCurvePoint(i / segments, curvePoint);
		if (i >= 1)
		{
			//Draw the segment line
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			SDL_RenderDrawLine(renderer, previousCurvePoint.x, previousCurvePoint.y, curvePoint.x, curvePoint.y);
		}
		previousCurvePoint = curvePoint;
	}
}

//Find the length of the current segment line
float Bezier::getCurrentSegmentLength(Vector2 currentPosition, SDL_Renderer *renderer) const
{
	Vector2 curvePoint;
	Vector2 previousCurvePoint;

	float segmentLength = 0.0f;

	for (float i = 0; i <= approximateSegments; i++)
	{
		curvePoint = findCurvePoint(i / approximateSegments, curvePoint);
		if (i >= 1)
		{
			//If current position is on the segment line
			if (distance(curvePoint, currentPosition) < distance(previousCurvePoint, currentPosition))
			{
				//Get segment length
				segmentLength = distance(curvePoint, previousCurvePoint);
				//Draw current segment
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawLine(renderer, previousCurvePoint.x, previousCurvePoint.y, curvePoint.x, curvePoint.y);
			}
		}
		previousCurvePoint = curvePoint;
	}

	return segmentLength;
}

//Find the distance between two points
float distance(Vector2 point1, Vector2 point2)
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

//Applies the quadratic bezier formula to find the current curve point
Vector2 Bezier::findCurvePoint(float t, Vector2 point) const
{
	point.x = pow(1-t, 3) * p0.x + 3 * pow(1 - t, 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
	point.y = pow(1 - t, 3) * p0.y + 3 * pow(1 - t, 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
	return point;
}

//Applies the quadratic bezier formula to find the current curve tangent
Vector2 Bezier::findCurveTangent(float t, Vector2 tangent) const
{
	tangent.x = 3 * pow(1 - t, 2) * (p1.x - p0.x) + 6 * (1 - t) * t * (p2.x - p1.x) + 3 * pow(t, 2) * (p3.x - p2.x);
	tangent.y = 3 * pow(1 - t, 2) * (p1.y - p0.y) + 6 * (1 - t) * t * (p2.y - p1.y) + 3 * pow(t, 2) * (p3.y - p2.y);
	return tangent;
}
