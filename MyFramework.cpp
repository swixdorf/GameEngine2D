#include "MyFramework.h"
Scene* MyFramework::currentScene;
Scene* MyFramework::nextScene;
int MyFramework::width = 800;
int MyFramework::height = 600;
bool MyFramework::fullscreen = false;
float MyFramework::frameLimitDelta = 1000 / 60; // Tick Per Second
unsigned int MyFramework::lastFrameTick = 0;

void MyFramework::PreInit(int& _width, int& _height, bool& _fullscreen)
{
	_width = width;
	_height = height;
	_fullscreen = fullscreen;
}

bool MyFramework::Init() {
	return true;
}

void MyFramework::Close() {

}
void MyFramework::setScene(Scene* scene)
{
	nextScene = scene;
}
bool MyFramework::Tick() {
	if (currentScene != nextScene && nextScene != nullptr)
	{
		currentScene = nextScene;
		nextScene = nullptr;
		currentScene->LoadScene(MyFramework::width, MyFramework::height);
	}

	//drawTestBackground();

	if (currentScene != nullptr)
	{
		unsigned int currentTick = getTickCount();
		if (currentTick - lastFrameTick > frameLimitDelta)
		{
			currentScene->Tick();
			lastFrameTick = getTickCount();
		}
		currentScene->Render();
	}
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {

}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (button == FRMouseButton::LEFT)
		currentScene->inputEvent(eInputCode::LMOUSE, isReleased);
	else if (button == FRMouseButton::RIGHT)
		currentScene->inputEvent(eInputCode::RMOUSE, isReleased);
}

void MyFramework::onKeyPressed(FRKey k) {
	switch (k)
	{
	case FRKey::LEFT: currentScene->inputEvent(eInputCode::LEFT); break;
	case FRKey::RIGHT: currentScene->inputEvent(eInputCode::RIGHT); break;
	case FRKey::UP: currentScene->inputEvent(eInputCode::UP); break;
	case FRKey::DOWN: currentScene->inputEvent(eInputCode::DOWN); break;
	}
}

void MyFramework::onKeyReleased(FRKey k) {
	switch (k)
	{
	case FRKey::LEFT: currentScene->inputEvent(eInputCode::LEFT, true); break;
	case FRKey::RIGHT: currentScene->inputEvent(eInputCode::RIGHT, true); break;
	case FRKey::UP: currentScene->inputEvent(eInputCode::UP, true); break;
	case FRKey::DOWN: currentScene->inputEvent(eInputCode::DOWN, true); break;
	}
}

const char* MyFramework::GetTitle()
{
	return "DURANGUL";
}