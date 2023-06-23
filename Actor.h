#pragma once
#include "SpriteMapper.h"
#include "GameObject.h"
enum eAnim {
	IDLE = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	SHOT,
	SHOT_LEFT,
	SHOT_RIGHT,
	SIZE // Last Element For size calculation hack
};


class Actor :public GameObject {
private:
	std::shared_ptr<SpriteEx> animBook[eAnim::SIZE];
public:
	eAnim currentAnim = eAnim::IDLE;
	Actor(std::string anims[eAnim::SIZE]);
	void Animate(eAnim targetSprite = eAnim::IDLE);
};
