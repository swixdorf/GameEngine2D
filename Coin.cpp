#include "Coin.h"
Coin::Coin(std::shared_ptr<SpriteEx> _sprite, _vec2 _pos,ShopController* _shopController) : GameObject(_sprite, _pos)
{
	shopController = _shopController;
}