#pragma once
#include "Scene.h"

#include "CollisionController.h"
#include "CharacterController.h"

#include "ShopController.h"
class SampleScene :public Scene {

public:
	void LoadScene(int width, int heigth);
	void Release();
	void Tick();
	void Render(int w, int h);
};

