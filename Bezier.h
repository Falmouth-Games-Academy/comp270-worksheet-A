#pragma once

#include "Vector2.h"

class Bezier
{
public:
	Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

	void draw(SDL_Renderer *renderer) const;

	Vector2 get_curve_point(float t) const;
	float get_move_percentage(float current_position, float move_speed);


private:

	Vector2 p0, p1, p2, p3;

	float get_distance(Vector2 pos_1, Vector2 pos_2);

};
