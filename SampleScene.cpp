#include "SampleScene.h"

#include "MyFramework.h"

void SampleScene::LoadScene(int width, int height)
{
	viewport.width = width;
	viewport.height = height;
	std::string anims[eAnim::SIZE] = { "bunny-left", "bunny-left", "bunny-right", "bunny-puca", "bunny-left-odskok", "bunny-right-odskok" };
	activePlayer = std::shared_ptr<Actor>(new Actor(anims));
	activePlayer->show(_vec2(width / 2, height - 100));
	std::cout << "SampleScene Load\n";
	activePlayer->bindController(new CharacterController(this));
	activePlayer->bindController(new CollisionController(this, activePlayer));
	auto shopController = new ShopController(this, activePlayer);
	activePlayer->bindController(shopController);
	activeCamera = new Camera(_rect(width, height), activePlayer);
	activeCamera->moveRel(0, -20);
	auto platformSprite = SpriteMapper::getInstance()->get("platform-green");

	int platformCount = (int)ceil(width / (*platformSprite).width);
	for (int i = 0; i <= platformCount; i++)
	{
		auto tmpGO = addToScene(new GameObject(SpriteMapper::getInstance()->get("platform-green"), _vec2((*platformSprite).width * i, height)));
		//	*tmpGO->bindController(new CollisionController(this, tmpGO));
	}
	addToScene(new GameObject(SpriteMapper::getInstance()->get("platform-green"), _vec2(50, height - 150)));

	addToScene(new Coin(SpriteMapper::getInstance()->get("coin"), _vec2(200, height - 50), shopController));
	addToScene(new GameObject(SpriteMapper::getInstance()->get("platform-red"), _vec2(width - 100, height - 100)));
	//addToScene(new GameObject(SpriteMapper::getInstance()->get("platform-green"), _vec2(0,0)));
}

void SampleScene::Release()
{

}
void SampleScene::Tick() {
	static _vec2 lastCameraPos = _vec2(0, 0);
	if (lastCameraPos.y != activeCamera->pos.y)
	{
		int minX = 100;
		int maxX = viewport.width - 100 - minX;
		int minY = 100;
		int maxY = (int)(viewport.height * 0.5 - minY);

		for (int i = 0; i < 3; i++)
		{
			int rndX = ((int)((rand() % maxX + minX) / 10) * 10);
			int rndY = ((int)((rand() % maxY + minY) / 10) * 10);
			std::string name = rand() % 5 == 0 ? "platform-red" : "platform-green"; // %20 chance %300
			addToScene(new GameObject(SpriteMapper::getInstance()->get(name), _vec2(rndX, rndY - activeCamera->pos.y)));
		}

		lastCameraPos = activeCamera->pos;

#if DEBUG_MODE
		std::cout << "Camera Moved Generating obstacles CAMERA POS:" << activeCamera->pos.y << std::endl;
#endif
	}

	Scene::Tick();

	if (activeCamera != nullptr)
		activeCamera->Tick();
	for (auto& gameObject : sceneObjects)
		gameObject->Tick();
	if (activePlayer != nullptr)
		activePlayer->Tick();
}
void SampleScene::Render(int w, int h)
{
	if (activePlayer != nullptr)
		activePlayer->Render(activeCamera->pos);
	for (auto& gameObject : sceneObjects)
	{
		gameObject->Render(activeCamera->pos);
	}
}