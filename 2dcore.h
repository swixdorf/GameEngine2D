#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include "Framework.h"

#define DEBUG_MODE	1

enum D {
	L = 1, //LEFT
	R = 2, //RIGHT
	T = 4, //TOP
	B = 8  //BOTTOM
};

struct _vec2
{
	int x = -1;
	int y = -1;
	bool init = false;
	_vec2() {}
	_vec2(int _x, int _y)
	{
		x = _x;
		y = _y;
		init = true;
	}
	_vec2 zero()
	{
		x = 0;
		y = 0;
		init = true;
		return *this;
	}
	_vec2 operator+(const _vec2& other) {
		return _vec2(x + other.x, y + other.y);
	}
	_vec2 operator+=(const _vec2& other) {
		x = x + other.x;
		y = y + other.y;
	}
	_vec2 operator-(const _vec2& other) {
		return _vec2(x - other.x, y - other.y);
	}
	_vec2 operator-=(const _vec2& other) {
		x = x - other.x;
		y = y - other.y;
	}
	void operator=(const _vec2& other) {
		x = other.x;
		y = other.y;
	}
};
struct _rect {
public:
	_vec2 anchor;
	int width;
	int height;
	_rect(int _width = 0, int _height = 0)
	{
		width = _width;
		height = _height;
		anchor = _vec2().zero();
	}
};
class Object2D :public  _rect
{
public:
	_vec2 anchor = _vec2().zero();
	_vec2 pos;
	Object2D(_vec2 _pos = _vec2())
	{
		if (_pos.init)
			pos = _pos;
	}
	void moveAbs(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void moveRel(int x, int y)
	{
		pos.x += x;
		pos.y += y;
	}
};

class SpriteEx :public  Object2D {
public:
	std::string name;
	Sprite* sprite;

	_vec2 offset = _vec2().zero();
	SpriteEx(std::string spriteName)
	{
		name = spriteName;
		auto fileName = std::filesystem::current_path().string().append("\\assets\\").append(spriteName).append(".png");
		sprite = createSprite(fileName.c_str());
		getSpriteSize(sprite, width, height);
#if DEBUG_MODE
		std::cout << "Sprite Loaded :" << name << " w: " << width << " h: " << height << std::endl;
#endif
	}
	~SpriteEx() {
#if DEBUG_MODE
		std::cout << "Sprite Unloaded :" << name << std::endl;
#endif
		destroySprite(sprite);
	}
	void Draw(_vec2 worldPos)
	{
		drawSprite(sprite, worldPos.x + offset.x, worldPos.y + offset.y);
	}
};


enum eInputCode {
	LEFT = 1,
	RIGHT = 2,
	UP = 4,
	DOWN = 8,
	LMOUSE = 16,
	RMOUSE = 32
};

class Controller {
public:
	virtual void Tick() = 0;
	virtual void inputEvent(eInputCode key, bool isUp = false) = 0;
};


