#pragma once
#include "Body.h"
#include "raymath.h"

inline void ExplictIntegrator( Body& body,float timestep) {
	body.position += body.velocity * timestep;
	body.velocity += body.acceleration * timestep;
	//velocity *= 1.0f / (1.0f + (damping * dt));
}

inline void SemiExplictIntegrator(Body& body, float timestep) {
	body.velocity += body.acceleration * timestep;
	body.velocity *= 1.0f / (1.0f + (body.damping * timestep));
	body.position += body.velocity * timestep;
}




