#pragma once
#include "raylib.h"
#include "math.h"
struct Polar {
public:
	Polar() = default;
	Polar(float angle, float radius) : m_angle{angle}, m_radius{radius} {}
	Polar(const Vector2& v) : m_angle{ atan2f(v.y, v.x) },m_radius{ sqrtf(v.x * v.x + v.y * v.y)	} {}

	Polar& operator = (const Vector2& v) {
		//get angle from vector
		m_angle = atan2(v.y, v.x);
		//get radius from vector
		m_radius = sqrt(v.x * v.x + v.y * v.y);

		return *this;
	}

	operator Vector2() const {
		Vector2 v;
		v.x = cos(m_angle) * m_radius;
		v.y = sin(m_angle) * m_radius;
		return v;
	}


public:
	float m_angle{ 0 };
	float m_radius{ 0 };
};