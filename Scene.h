#pragma once
#include "Actor.h"
#include "Camera.h"

class Scene {

public:
	_rect viewport;
	unsigned int tickCounter = 0;
	std::vector<std::shared_ptr<GameObject>> sceneObjects;
	std::shared_ptr<Actor> activePlayer;
	Camera* activeCamera;
	virtual void LoadScene(int width,int height) = 0;
	virtual void Tick() { tickCounter++; };
	virtual void Render(int w = 800, int h = 400) = 0;
	std::shared_ptr<GameObject> addToScene(GameObject* _go);
	void removeFromScene(GameObject _go);
	void inputEvent(eInputCode key, bool isUp = false);
};

