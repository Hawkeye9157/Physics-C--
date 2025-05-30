#include "VectorScene.h"
#include "Body.h"
#include "ZaWorldo.h"
#include "grav.h"
#include "MathUtils.h"
#include "raymath.h"
#include "raygui.h"



void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2,
		static_cast<float>(m_height) / 2 });
	m_world = new World();
	m_world->Initialize();


	
	
}

void VectorScene::Update()
{
	float dt = (float)GetFrameTime();

	float theta = randf(0, 360);


	if (!mouseOverGUI && IsMouseButtonPressed(0)) {
		Vector2 pos = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++) {
			
			Body* body = m_world->CreateBody(pos, SizeSliderValue, ColorFromHSV(randf(360), 1, 1));
			float offset = randf(-180, 180);
			float x = cosf((theta * offset) * DEG2RAD);
			float y = sinf((theta * offset) * DEG2RAD);
			body->velocity = Vector2{ x,y} * randf(1,6);
			body->gravityScale = ScaleSliderValue;
		}
	}
	

	//apply collision
	for (auto body : m_world->GetBodies()) {
		if (body->position.y < -5) {
			body->position.y = -5;
			//body->velocity.y * -body->restitution;
		}
	}
}

void VectorScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10,5,DARKGRAY);
	m_world->Draw(*this);
	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	//mouseOverGUI = PhysicsWindowBoxActive && CheckCollisionPointRec(GetMousePosition(),
	//	{ anchor01.x + 0, anchor01.y + 0, 288, 440 });
	//if (BodyTypeDropdownEditMode) GuiLock();

	//if (PhysicsWindowBoxActive)
	//{
	//	PhysicsWindowBoxActive = !GuiWindowBox(Rectangle { anchor01.x + 0, anchor01.y + 0, 288, 440 }, "Physics");
	//	GuiSlider(Rectangle { anchor01.x + 64, anchor01.y + 48, 120, 16 }, "Gravity", NULL, & GravitySliderValue, -20, 20);
	//}
	//GuiGroupBox(Rectangle { anchor02.x + 0, anchor02.y + 0, 216, 200 }, "Body");
	//GuiSlider(Rectangle { anchor02.x + 80, anchor02.y + 24, 120, 16 }, "Mass", NULL, & MassSliderValue, 0, 5);
	//GuiSlider(Rectangle { anchor02.x + 80, anchor02.y + 56, 120, 16 }, "Size", NULL, & SizeSliderValue, 0, 5);
	//GuiSlider(Rectangle { anchor02.x + 80, anchor02.y + 88, 120, 16 }, "Gravity Scale", NULL, & ScaleSliderValue, 0, 5);
	//GuiSlider(Rectangle { anchor02.x + 80, anchor02.y + 120, 120, 16 }, "Damping", NULL, & DampingSliderValue, 0, 5);
	////if (GuiDropdownBox(Rectangle { anchor02.x + 80, anchor02.y + 152, 120, 24 }, NULL, & BodyTypeDropdownActive,
	////	BodyTypeDropdownEditMode)) BodyTypeDropdownEditMode = !BodyTypeDropdownEditMode;

	//GuiUnlock();
}

void VectorScene::FixedUpdate()
{
	m_world->Step(Scene::fixedTimeStep);
	ApplyGravitation(m_world->GetBodies(),1);
}
