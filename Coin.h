#pragma once
#include "GameObject.h"

#include "ShopController.h"
class Coin : public GameObject
{
public:
	ShopController* shopController;
	Coin(std::shared_ptr<SpriteEx> _sprite, _vec2 _pos, ShopController* shopController);
};

