#pragma once
#include "2dcore.h"
#include "Scene.h"
class ShopController :public Controller
{
public:
	Scene* currentScene;
	int currentKeyState;
	int prevKeyState;
	int coin = 0;
	ShopController(Scene* _currentScene, std::shared_ptr<GameObject> selfGameObject)
	{
		currentScene = _currentScene;
	}
	void Tick()
	{


	}

	void inputEvent(eInputCode key, bool isUp = false)
	{

		prevKeyState = currentKeyState;
		if (!isUp)
		{
			if (key == eInputCode::RMOUSE)
			{
				if (coin >= 20)
				{
					coin -= 20;
					std::cout << "Ability Used Cost: 20 Remaining Coin :" << coin << std::endl;
				}
				else
				{
					std::cout << "Insufficient Coins To Use Ability" << std::endl;
				}
			}
			currentKeyState = currentKeyState + key;
		}
		else
			currentKeyState &= ~key;

	}

};

