#pragma once
#include <raylib.h>

struct AABB {
public:
	Vector2 center;
	Vector2 size;

	AABB(const Vector2& center,const Vector2& size) : center{center},size {size} {}

	Vector2 extents() const { return Vector2{ size.x / 2,size.y / 2 }; }
	Vector2 min() const {return Vector2{ center.x - size.x,center.y - size.y }; }
	Vector2 max() const { return Vector2{ center.x + size.x,center.y + size.y }; }
};