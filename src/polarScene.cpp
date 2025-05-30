#include "polarScene.h"
#include <Polar.h>
#include "raymath.h"
float randfloat() {
	return rand() / (float)RAND_MAX;
}

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
	m_camera->BeginMode();

	Color color;
	color.r = randfloat() * 255;
	color.g = randfloat() * 255;
	color.b = randfloat() * 255;
	color.a = 255;

	//Archimedean
	/*int steps = 200;
	float time = (float)GetTime();
	float a = 0;
	float b = 0.35f;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps * (8 * PI));
		float r = a + (b * theta);
		Polar p(time + theta, r);
		DrawCircle(p, 0.2f, color);
	}*/

	//Cardioid
	/*int steps = 200;
	float a = 3;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps * (8 * PI));
		float r = a * (1 + cosf(theta));
		Polar p(theta, r);
		DrawCircle(p, 0.2f, color);
	}*/

	//Limacon
	/*int steps = 200;
	float a = 1;
	float b = 2;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps * (8 * PI));
		float r = a + (b * cosf(theta));
		Polar p(theta, r);
		DrawCircle(p, 0.2f, color);
	}*/

	//rose curve
	/*int steps = 200;
	float a = 3;
	float k = 3;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps * (8 * PI));
		float r = a * cosf(theta * k);
		Polar p(theta, r);
		DrawCircle(p, 0.2f, color);
	}*/

	//Clint's Curve
	int steps = 200;
	float a = 2.5;
	a =randfloat() * 3;
	float b = 1;
	b = randfloat() * 3;
	float k = 6;
	k =  randfloat() * 6;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps * (8 * PI));
		float r = (a * (cosf(b)) + b * (sinf(a))) * (a * cosf(theta * k));
		Polar p(theta, r);
		DrawCircle(p, 0.2f, color);
	}




	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}

void PolarScene::FixedUpdate()
{
}

