
#include "Actor.h"

Actor::Actor(std::string anims[eAnim::SIZE]) {
	SpriteMapper* spMapper = SpriteMapper::getInstance();
	for (int i = 0; i < eAnim::SIZE; i++)
		animBook[i] = spMapper->get(anims[i]);
	Animate();
}
void Actor::Animate(eAnim targetSprite) {
	currentAnim = targetSprite;
	sprite = animBook[currentAnim];
	width = (*sprite).width;
	height = (*sprite).height;
}