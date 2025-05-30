#include "FireworkScene.h"

void FireworkScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, 
		static_cast<float>(m_height) / 2 });
}

void FireworkScene::Update()
{
}

void FireworkScene::Draw()
{
}

void FireworkScene::DrawGUI()
{
}

void FireworkScene::FixedUpdate()
{
}
