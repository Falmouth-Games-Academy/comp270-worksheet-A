#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
	for (int i = 0; i < CURVEYSAMPLES + 1; i++)
	{
		incrementalPoints[i] = CalculateBezier(float(i) / CURVEYSAMPLES);
	}
}

void Bezier::draw(SDL_Renderer *renderer) const
{
	for (int i = 0; i < CURVEYSAMPLES; i++)
	{
		SDL_RenderDrawLineF(renderer, incrementalPoints[i].x, incrementalPoints[i].y, incrementalPoints[i + 1].x, incrementalPoints[i + 1].y);
	}
}

Vector2 Bezier::CalculateBezier(float t)
{
	Vector2 bezierCurvePoints = Vector2();
	bezierCurvePoints = pow((1.0f - t), 3.0f)*p0 + 3.0f * pow((1.0f - t), 2.0f)*t*p1 + 3.0f * (1.0f - t) * pow(t, 2.0f) * p2 + pow(t, 3.0f) * p3;
	return bezierCurvePoints;
}

float Bezier::calculateRotation(float t)
{
	Vector2 tan = (3 * pow((1 - t), 2) * (p1 - p0) + 6 * (1 - t) * t * (p2 - p1) + 3 * pow(t, 2) * (p3 - p2));
	float theta = atan2f((float)tan.x, (float)tan.y);
	float degrees = 180 - theta * (180 / 3.14159265358);
	return degrees;
}


