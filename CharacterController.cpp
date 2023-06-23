#include "CharacterController.h"
#include "CollisionController.h"
CharacterController::CharacterController(Scene* scene)
{
	currentScene = scene;
}
void CharacterController::inputEvent(eInputCode key, bool isUp) {
	prevKeyState = currentKeyState;
	if (!isUp)
		currentKeyState = currentKeyState + key;
	else
		currentKeyState &= ~key;
}

void CharacterController::Jump(int height, int durationMS) {
	jumpStartHeight = currentScene->activePlayer.get()->pos.y;
	isFalling = false;
	jumpHeight = height;
	jumpDuration = durationMS;
	jumpStartTime = getTickCount();
}
void CharacterController::Tick() {

	auto currentPlayer = currentScene->activePlayer.get();

	if (currentPlayer->pos.x > currentScene->viewport.width / 2)
		moveMultiplier = 9;
	else
		moveMultiplier = 6;

	if (isFalling)
	{
		if (currentPlayer->collisionController->colType & D::B)
		{
			Jump(200 * (currentPlayer->collisionController->is300 ? 3 : 1), 1000);
		}
		else {
			currentPlayer->moveRel(0, 5);

		}
	}
	else
	{
		if (currentPlayer->pos.y > jumpStartHeight - jumpHeight && !(currentPlayer->collisionController->colType & D::T))
		{
			int hDelta = 0;
			int elapsedTime = getTickCount() - jumpStartTime;
			int currentH = currentPlayer->pos.y;
			if (elapsedTime < jumpDuration / 2)
			{
				hDelta = ((currentH - (jumpStartHeight - jumpHeight)) * 5 * jumpHeight / 15) / (jumpDuration - elapsedTime);
			}
			hDelta++;
			currentPlayer->moveRel(0, -1 * hDelta);
		}
		else
			isFalling = true;
	}
	if (currentKeyState & eInputCode::RIGHT)
	{
		if (currentPlayer->pos.x + currentPlayer->width + moveMultiplier < currentScene->viewport.anchor.x + currentScene->viewport.width)
		{
			currentPlayer->moveRel(moveMultiplier, 0);
			currentPlayer->Animate(eAnim::MOVE_RIGHT);
		}
	}
	else if (currentKeyState & eInputCode::LEFT)
	{
		if (currentPlayer->pos.x - moveMultiplier > currentScene->viewport.anchor.x)
		{
			currentPlayer->moveRel(moveMultiplier * -1, 0);
			currentPlayer->Animate(eAnim::MOVE_LEFT);
		}
	}

	if (currentKeyState & eInputCode::UP)
	{
		currentScene->activeCamera->moveRel(0, 5);
	}
	else if (currentKeyState & eInputCode::DOWN)
	{
		currentScene->activeCamera->moveRel(0, -5);
	}
}