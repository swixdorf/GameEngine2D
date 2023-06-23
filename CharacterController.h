#pragma once
#include "Scene.h"


class CharacterController :public Controller {
public:
	int currentKeyState;
	int prevKeyState;
	Scene* currentScene;
	int moveMultiplier = 6;
	bool isFalling = true;
	int jumpStartHeight = 0;
	int jumpHeight = 0;
	int jumpDuration = 0;
	int jumpStartTime = 0;
	CharacterController(Scene* scene);
	void inputEvent(eInputCode key, bool isUp = false);
	std::shared_ptr<Actor> getActivePlayer();
	void Jump(int height, int durationMS);
	void Tick();
};
