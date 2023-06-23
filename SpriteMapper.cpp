#include "SpriteMapper.h"
SpriteMapper* SpriteMapper::_instance;
SpriteMapper* SpriteMapper::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteMapper();
	return _instance;
}

SpriteMapper::SpriteMapper() { // singleton
#if DEBUG_MODE
	std::cout << "SpriteMapper Init" << std::endl;
#endif
}
std::shared_ptr<SpriteEx> SpriteMapper::get(std::string spriteName)
{
	for (auto& sprite : loadedSprites)
		if (sprite->name == spriteName)
			return sprite;

	std::shared_ptr<SpriteEx> ptr = std::make_shared< SpriteEx>(spriteName);
	loadedSprites.push_back(ptr);
	return ptr;
}


