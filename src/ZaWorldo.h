#pragma once
#include "Body.h"
#include "Spring.h"
#include <vector>
#include <raylib.h>

class Scene;

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;

class World {
public:
	World() = default;
	~World();
	

	void Initialize(Vector2 gravity = Vector2{ 0,-09.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position,float mass, float size, const Color& color);
	Spring* CreateSpring(Body* a, Body* b, float restLength, float stiffness, float damping);
	void Step(float dt);
	void Draw(const Scene& scene);

	void Detonate();

	bodies_t& GetBodies() { return m_bodies; }
	inline static Vector2 m_gravity {0,-9.81f};
	inline static float gravitation = 0.0f;
	inline static float springStiffnessMultiplier = 1;
	inline static bool simulate = true;



private:
	bodies_t m_bodies;
	springs_t m_springs;


};