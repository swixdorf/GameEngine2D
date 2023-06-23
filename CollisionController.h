#pragma once
#include "Scene.h"
#include "Coin.h"
#include <set>

class CollisionController : public Controller
{

public:
	Scene* currentScene;
	std::shared_ptr<GameObject> self;
	std::shared_ptr<GameObject> debugObj;
	std::set<std::shared_ptr<GameObject>> collidingObjects;
	int colType = 0;
	bool is300 = false;
	CollisionController(Scene* _currentScene, std::shared_ptr<GameObject> selfGameObject);
	void Tick();

	void inputEvent(eInputCode key, bool isUp = false)
	{

	}
	void collisionStart(std::shared_ptr<GameObject> other);
	void colliding(std::shared_ptr<GameObject> other);
	void collisionEnd(std::shared_ptr<GameObject> other);
};

