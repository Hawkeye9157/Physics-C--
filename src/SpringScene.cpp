#include "SpringScene.h"
#include "ZaWorldo.h"
#include "Gui.h"
#include "MathUtils.h"
#include "Body.h"
#include <raymath.h>


void SpringScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{static_cast<float>(m_width) / 2,static_cast<float>(m_height) / 2});
	m_world = new World();
	m_world->Initialize();
}

void SpringScene::Update()
{
	float dt = GetFrameTime();
	if (!GUI::mouseOverGUI) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::bodyTypeActive;

			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, ColorFromHSV(randf(360), 1, 1));

			body->restitution = GUI::restitutionValue;
			body->gravityScale = GUI::gravityScaleValue;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
		if (m_selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else {
				if (m_selectedBody && m_connectedBody)
				{
					float distance = Vector2Distance(m_selectedBody->position, m_connectedBody->position);
					m_world->CreateSpring(m_selectedBody, m_connectedBody, distance, GUI::stiffnessValue, GUI::dampingValue);
				}

				m_selectedBody = nullptr;
				m_connectedBody = nullptr;
			}
		}
	}
	//apply collision
	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x); // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);  // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
	}

	GUI::Update();
}

void SpringScene::FixedUpdate()
{
	m_world->Step(Scene::fixedTimeStep);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, BLUE);
	m_world->Draw(*this);
	if (m_selectedBody)
	{

		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);
		if (m_connectedBody)
		{
			DrawCircleLine(m_connectedBody->position, m_connectedBody->size, YELLOW, 5);
			DrawLine(m_selectedBody->position, m_connectedBody->position, 3, GREEN);
		}
		else {
			DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}
	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}
