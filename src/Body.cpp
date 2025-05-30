#include "Body.h"
#include "Integrator.h"
#include "raymath.h"
#include "scene.h"
#include "ZaWorldo.h"

void Body::Step(float dt)
{
	if (type != Type::DYNAMIC) return; //your not wanted
	force += (World::m_gravity * gravityScale) * mass;
	velocity = (force * invMass);

	SemiExplictIntegrator(*this, dt);

	
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force,ForceMode forcemode)
{
	switch (forcemode)
	{
	case Body::ForceMode::FORCE:
		this->force += force;
		break;
	case Body::ForceMode::IMPULSE:
		this->velocity += force * invMass;
		break;
	case Body::ForceMode::VELOCITY:
		this->velocity += force;
		break;
	default:
		break;
	}
}


