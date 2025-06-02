#pragma once
#include <raylib.h>

struct Contact {
public:
	struct Body* bodyA;
	struct Body* bodyB;

	float restitution;
	float depth;
	Vector2 Normal;



};