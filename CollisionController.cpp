#include "CollisionController.h"

CollisionController::CollisionController(Scene* _currentScene, std::shared_ptr<GameObject> selfGameObject)
{
	currentScene = _currentScene;
	self = selfGameObject;
#if DEBUG_MODE
	debugObj = currentScene->addToScene(new GameObject(SpriteMapper::getInstance()->get("collision"), _vec2(0, 0)));
	debugObj->isCollide = false;
#endif	
}


void CollisionController::Tick()
{
	debugObj->pos = self->pos;
	colType = 0;
	is300 = false;
	for (auto& gO : currentScene->sceneObjects)
		if (gO != nullptr && gO->isCollide)
		{
			int isColliding = (*self) & (*gO);
			if (isColliding)
			{
				colType |= isColliding;
				if (collidingObjects.find(gO) == collidingObjects.end())
				{
					collisionStart(gO);
					collidingObjects.insert(gO);
					is300 |= gO->sprite->name == "platform-red";
				}
				else
					colliding(gO);
			}
			else
			{
				if (collidingObjects.find(gO) != collidingObjects.end())
				{
					collisionEnd(gO);
					collidingObjects.erase(gO);
				}
			}
		}
}
void CollisionController::collisionStart(std::shared_ptr<GameObject> other)
{
	if (other->sprite->name == "coin")
	{

		auto downcastedPtr = std::reinterpret_pointer_cast<Coin>(other);
		downcastedPtr->shopController->coin += 50;
		std::cout << "Current Coin Updated " << downcastedPtr->shopController->coin << std::endl;
		currentScene->removeFromScene((*other));
		colType = 0;
	}
#if DEBUG_MODE
	//std::cout << "Collision Start Between : " << self.get()->id << " and " << other->id << " Type : " << colType << std::endl;
#endif
}
void CollisionController::colliding(std::shared_ptr<GameObject> other)
{
#if DEBUG_MODE
	//	std::cout << "Colliding Between : " << self.get()->id << " and " << other->id << std::endl;
#endif
}
void CollisionController::collisionEnd(std::shared_ptr<GameObject> other)
{
#if DEBUG_MODE
	//std::cout << "Collision END Between : " << self.get()->id << " and " << other->id << std::endl;
#endif
}