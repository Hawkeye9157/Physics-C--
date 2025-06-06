#pragma once
#include "scene.h"

class SpringScene : public Scene {
public:
	SpringScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background) { }

	// Inherited via Scene
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;
private:
	Body* m_selectedBody{ nullptr };
	Body* m_connectedBody{ nullptr };
};