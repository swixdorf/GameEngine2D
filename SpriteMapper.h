#pragma once
#include "2dcore.h"
class SpriteMapper {
private:
	static SpriteMapper* _instance;
	std::vector<std::shared_ptr<SpriteEx>> loadedSprites;
	SpriteMapper();
public:
	static SpriteMapper* getInstance();
	std::shared_ptr<SpriteEx> get(std::string spriteName);
};
//
