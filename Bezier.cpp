#include "stdafx.h"
#include "Bezier.h"
#include <math.h>

Bezier::Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
	: p0(p0), p1(p1), p2(p2), p3(p3)
{
}

Vector2 Bezier::get_curve_point(float t) const
{
	Vector2 curve_point = Vector2(0, 0);

	curve_point.x = (pow(1.0f - t, 3) * p0.x) + (3.0f * pow(1.0f - t, 2) * t * p1.x) + (3.0f * (1.0f - t) * pow(t, 2) * p2.x) + (pow(t, 3) * p3.x);
	curve_point.y = (pow(1.0f - t, 3) * p0.y) + (3.0f * pow(1.0f - t, 2) * t * p1.y) + (3.0f * (1.0f - t) * pow(t, 2) * p2.y) + (pow(t, 3) * p3.y);
	
	return curve_point;

}

float Bezier::get_move_percentage(float current_position, float move_distance)
{

	int iter = 500;

	Vector2 start_point = get_curve_point( current_position );
	Vector2 end_point = start_point;

	float distance_travled = 0;
	float percentage_moved = 0;

	// iterate over the curve to find has much distance we are going to travel
	for (int i = (int)(current_position * iter); i < iter; i++)
	{

		Vector2 current_point = get_curve_point((float)i / iter);
		distance_travled += get_distance(current_point, end_point);
		end_point = current_point;
		percentage_moved += 1.0f / iter;
		
		// exit the loop once we have exceed the amount of distance we want to travel
		if (distance_travled > move_distance) break;

	}

	// if we have not exceed the amount of distance we need to travle go to the end of the curve.
	if (distance_travled < move_distance)
		percentage_moved = 1.0f - current_position;

	return percentage_moved;

}

void Bezier::draw(SDL_Renderer *renderer) const
{

	Vector2 start_point = Vector2();
	Vector2 end_point = Vector2();
	int iter = 20;

	for (int i = 0; i < iter; i++)
	{

		start_point = get_curve_point( (float)i / (float)iter);
		end_point = get_curve_point( ((float)i + 1.0f) / (float)iter );

		SDL_RenderDrawLine(renderer, start_point.x, start_point.y, end_point.x, end_point.y);

	}


}

float Bezier::get_distance(Vector2 pos_1, Vector2 pos_2)
{

	Vector2 dif = pos_2 - pos_1;

	return sqrtf( pow(pos_2.x - pos_1.x, 2) + pow(pos_2.y - pos_1.y, 2) );

}
