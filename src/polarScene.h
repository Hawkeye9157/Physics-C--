#pragma once
#include "scene.h"
class PolarScene : public Scene {
public:
	PolarScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title,width,height,background) {}


	// Inherited via Scene
	void Initialize() override;

	void Update() override;

	void Draw() override;

	void DrawGUI() override;


	// Inherited via Scene
	void FixedUpdate() override;

};

