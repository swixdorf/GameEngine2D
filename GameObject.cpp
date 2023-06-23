#include "GameObject.h"
unsigned int GameObject::objCounter = 0;

GameObject::GameObject(std::shared_ptr<SpriteEx> _sprite, _vec2  _pos, bool _show, int _order)
{
	sprite = _sprite;
	pos = _pos;
	bShow = _show && pos.x >= 0 && pos.y >= 0;
	id = objCounter++;
	if (sprite != nullptr)
	{
		width = (*sprite).width;
		height = (*sprite).height;
	}
#if DEBUG_MODE
	std::cout << "Gameobject Construct(" << pos.x << "," << pos.y << ") ID: " << id << std::endl;
#endif
}

GameObject::~GameObject() {
#if DEBUG_MODE
	std::cout << "Gameobject Destroy" << std::endl;
#endif
}

bool GameObject::isVisible()
{
	return true;
	return bShow && sprite != nullptr && pos.x != -1;
}

GameObject* GameObject::bindController(Controller* controller)
{
	controllers.push_back(controller);
	return this;
}

GameObject* GameObject::bindController(CollisionController* controller)
{
	collisionController = controller;
	return bindController(reinterpret_cast<Controller*>(controller));
}


GameObject* GameObject::show(_vec2 _pos)
{
	if (_pos.init)
		pos = _pos;
	bShow = true;
	return this;
}

GameObject* GameObject::hide()
{
	bShow = false;
	return this;
}

void GameObject::Tick()
{
	for (auto controller : controllers)
		controller->Tick();
}

void GameObject::Render(_vec2 renderOffset) {
	if (isVisible())
	{
		sprite->Draw(pos + renderOffset);
	}
}

bool GameObject::operator==(GameObject const& other)
{
	return other.id == id;
}
int GameObject::operator&(GameObject const& other)
{
	int colType = 0;
	bool xCol, yCol;

	xCol = (pos.x < other.pos.x && (pos.x + width) >= other.pos.x) || (other.pos.x <= pos.x && (other.pos.x + other.width) >= pos.x);
	yCol = (pos.y < other.pos.y && (pos.y + height) >= other.pos.y) || (other.pos.y <= pos.y && (other.pos.y + other.height) >= pos.y);

	//xCol = (other.pos.x > pos.x && pos.x + width > other.pos.x - 2) || (other.pos.x <= pos.x && other.pos.x + other.width > pos.x - 2);
	//yCol = (other.pos.y > pos.y && pos.y + height > other.pos.y - 2) || (other.pos.y <= pos.y && other.pos.y + other.height > pos.y - 2);

	if (xCol && yCol)
	{
		colType |= (other.pos.x >= pos.x ? D::R : D::L);
		colType |= (other.pos.y >= pos.y ? D::B : D::T);
	}


#if DEBUG_MODE
	/*if (other.id == 17 || id == 17)
		std::cout << ":" << pos.y << "," << other.pos.y << ":" << height << "," << other.height << "||" << xCol << "-" << yCol << "_" << colType << "|";
	if (xCol)
	{
		std::cout << other.id << " : " << id << " > " << pos.y << ":" << other.pos.y << "|" << (other.pos.y > pos.y) << "  " << other.pos.y + other.width << " _ " << (other.pos.y + other.width > pos.y) << std::endl;
		if (yCol)
			std::cout << (xCol && yCol) << "-------------------------------------------------------" << std::endl;
	}*/
#endif
	return colType;
}