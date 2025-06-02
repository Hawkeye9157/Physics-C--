#include "Collision.h"
#include "raylib.h"
#include "raymath.h"
#include "MathUtils.h"
#include "Body.h"

 void Collision::CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++) {
		Body* bodyA = bodies[i];
		for (int j = 1; j < bodies.size(); j++) {
			Body* bodyB = bodies[j];
			if (bodyA->type != Body::Type::DYNAMIC || bodyB->type != Body::Type::DYNAMIC) continue;
			if (Intersects(bodyA, bodyB)) {
				Contact contact;
				contact.bodyA = bodyA;
				contact.bodyB = bodyB;

				Vector2 dir = { bodyB->position.x - bodyA->position.x,bodyB->position.y - bodyA->position.y };
				float distanceSqr = Vector2LengthSqr(dir);

				if (distanceSqr < EPSILON) {
					dir = Vector2{ randf(-0.05f,0.05f),randf(-0.05f,0.05f) };

					distanceSqr = Vector2LengthSqr(dir);
				}

				float distance = sqrtf(distanceSqr);
				float radius = bodyA->size + bodyB->size;
				contact.depth = (radius) - distance;
				contact.Normal = dir / distance;
				contact.restitution = (bodyA->restitution + bodyB->restitution) / 2;
				contacts.push_back(&contact);
			}
		}
	}
}

void Collision::SeperateContacts(contacts_t& contacts)
{
	for (auto contact : contacts) {
		float totalInverseMass = contact->bodyA->invMass + contact->bodyB->invMass;
		Vector2 seperation = contact->Normal * (contact->depth / totalInverseMass);
		contact->bodyA->position = contact->bodyA->position + (seperation * contact->bodyA->invMass);
		contact->bodyB->position = contact->bodyB->position + (seperation * contact->bodyB->invMass);
	}
}

bool Collision::Intersects(Body* bodyA, Body* bodyB)
{
	float distance = Vector2Distance(bodyA->position, bodyB->position);
	float radius = bodyA->size + bodyB->size;

	return (distance <= radius);
}
