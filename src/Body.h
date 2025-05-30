#pragma once
#include "raylib.h"
#include "scene.h"

struct Body {
public:
	enum class Type {
		STATIC,
		KINEMATIC,
		DYNAMIC
	};
	enum class ForceMode {
		FORCE,
		IMPULSE,
		VELOCITY
	};
public:
	friend class Scene;
	Body() = default;

	Body(const Vector2& pos,float size,const Color& col) :
		position{pos},size {size},color {col} {}

	Body(const Vector2& pos,const Vector2& vel, float size,const Color& col) :
		position {pos}, velocity{vel},size{size},color{col} { }

	Body(Type type, const Vector2& pos, float mass, float size, const Color& col) :
		type{ type }, position{ pos }, mass{ mass }, size{ size }, color{ col } {
		invMass = (type == Type::DYNAMIC && mass != 0) ? 1 / mass : 0;
	}


	void Step(float dt);
	void Draw(const Scene& scene);

	void ApplyForce(const Vector2& force, ForceMode forcemode = ForceMode::FORCE);

	void ClearForce() { force = Vector2{ 0 }; }

public:
	Vector2 position{ 0 };
	Vector2 velocity{ 0 };
	Vector2 acceleration{ 0 };
	Vector2 force{ 0 };

	float mass{ 1.0f };
	float invMass{ 1.0f };
	float damping{ 0.1f };
	float restitution{ 1 };

	float gravityScale{ 1.0f };

	float size{ 0.0f };
	Color color{ BLACK };

	Type type = Type::DYNAMIC;

	Body* next{ nullptr };
	Body* prev{ nullptr };
};