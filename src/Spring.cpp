#include "Spring.h"
#include "Body.h"
#include "raymath.h"
void Spring::ApplyForce( float kMultiplier)
{
	//get direction
	Vector2 dir = bodyA->position - bodyB->position;
	float lSqr = Vector2LengthSqr(dir);
	if (lSqr <= EPSILON) return;

	//calculate force
	float length = sqrtf(lSqr);
	float dis = length - restLength;
	float fMag = -(k * kMultiplier) * dis;

	Vector2 nDir = dir / length;
	Vector2 force = nDir * fMag;

	//damp the force
	Vector2 dv = bodyA->velocity - bodyB->velocity;
	float dFact = Vector2DotProduct(dv, nDir) * damping;
	Vector2  dForce = nDir * dFact;

	force -= dForce;

	//apply
	bodyA->ApplyForce(force);
	bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::ApplyForce(const Vector2& position, Body& body, float restLength, float k)
{
	Vector2 dir = position - body.position;
	float lSqr = Vector2LengthSqr(dir);
	if (lSqr <= EPSILON) return;
	//calculate force
	float length = sqrtf(lSqr);
	float dis = length - restLength;
	float fMag = -(k)*dis;
	Vector2 nDir = dir / length;
	Vector2 force = nDir * fMag;
	//apply
	body.ApplyForce(Vector2Negate(force));
}

void Spring::Draw(const Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 3, RED);
}
