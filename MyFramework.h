#pragma once



#include "Scene.h"

class MyFramework : public Framework {
private:
	static Scene* currentScene;
	static Scene* nextScene;
public:
	static int width;
	static int height;
	static bool fullscreen;
	static float frameLimitDelta;
	static unsigned int lastFrameTick;

	virtual void PreInit(int& _width, int& _height, bool& _fullscreen);
	virtual bool Init();
	virtual void Close();
	static void setScene(Scene* scene);
	virtual bool Tick();
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
	virtual void onKeyPressed(FRKey k);
	virtual void onKeyReleased(FRKey k);
	virtual const char* GetTitle();
};
