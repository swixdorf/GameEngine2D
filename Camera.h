#pragma once
#include "Actor.h"
class Camera :public GameObject {
public:
	_rect wP;
	std::shared_ptr<GameObject> gOFollow;
	Camera(_rect wP, std::shared_ptr<GameObject> _gOFollow = nullptr);
	void Tick();
};
