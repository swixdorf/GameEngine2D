#include "Scene.h"
std::shared_ptr<GameObject> Scene::addToScene(GameObject* _go)
{
	auto sPGO = std::shared_ptr<GameObject>(_go);
	sceneObjects.push_back(sPGO);
	return sPGO;
}
void Scene::removeFromScene(GameObject _go)
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		if ((*sceneObjects[i]) == _go)
		{
			sceneObjects.erase(sceneObjects.begin() + i);
		}
	}
}
void Scene::inputEvent(eInputCode key, bool isUp) {
	for (auto& controller : activePlayer->controllers)
	{
		controller->inputEvent(key, isUp);
	}
}