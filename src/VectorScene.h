#pragma once
#include "scene.h"

struct Body;
class VectorScene : public Scene {
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background) {
	}

private:
	// Inherited via Scene
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void DrawGUI() override;
	void FixedUpdate() override;

private:
	bool mouseOverGUI = false;

	Vector2 anchor01 = { 88, 80 };
	Vector2 anchor02 = { 120, 168 };

	bool PhysicsWindowBoxActive = true;
	float GravitySliderValue = 0.0f;
	float MassSliderValue = 1.0f;
	float SizeSliderValue = 1.0f;
	float ScaleSliderValue = 1.0f;
	float DampingSliderValue = 0.0f;
	bool BodyTypeDropdownEditMode = false;
	int BodyTypeDropdownActive = 0;
};