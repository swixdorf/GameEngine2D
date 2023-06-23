#pragma once
#include "2dcore.h"

class CollisionController;
class GameObject :public Object2D {
	friend class CollisionController;
	static unsigned int objCounter;
protected:
	std::shared_ptr<SpriteEx> sprite;
public:
	std::vector<Controller*> controllers;
	CollisionController* collisionController;
	bool isCollide = true;
	unsigned int id = 0;

	int renderOrder = 0;
	bool bShow = false;
	GameObject(std::shared_ptr<SpriteEx> _sprite = nullptr, _vec2 _pos = _vec2(), bool _show = true, int _order = 0);
	~GameObject();
	bool isVisible();
	GameObject* bindController(Controller* controller);
	GameObject* bindController(CollisionController* controller);
	GameObject* show(_vec2 _pos);
	GameObject* hide();
	void Tick();
	void Render(_vec2 renderOffset = _vec2().zero());
	bool operator==(GameObject const& other);
	int operator&(GameObject const& other);
};

