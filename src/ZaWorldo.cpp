#include "ZaWorldo.h"
#include "Body.h"
#include <Collision.h>
#include <grav.h>



World::~World()
{

}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
	m_gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);
    return body;
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

Spring* World::CreateSpring(Body* a, Body* b, float restLength, float stiffness, float damping)
{
    Spring* spring = new Spring(a,b,restLength,stiffness,damping);

    return spring;
}

void World::Step(float dt)
{
    if (!simulate) return;

    if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);
    for (auto spring : m_springs) {
        spring->ApplyForce(0.5f, 1.0f);
    }
    for (auto body : m_bodies) {
        body->Step(dt);
        body->ClearForce();
    }
    m_contacts.clear();
    Collision::CreateContacts(m_bodies, m_contacts);
    Collision::SeperateContacts(m_contacts);
}

void World::Draw(const Scene& scene)
{
    for (auto body : m_bodies) {
        body->Draw(scene);
    }
}

void World::Detonate()
{
    for (auto body : m_bodies) {
        delete body;
    }
}


