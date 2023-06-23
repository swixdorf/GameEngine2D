#include "Camera.h"
Camera::Camera(_rect _wP, std::shared_ptr<GameObject> _gOFollow) {
	gOFollow = _gOFollow;
	wP = _wP;
}
void Camera::Tick() {
	GameObject::Tick();
	if (gOFollow != nullptr)
	{
		if ((wP.height - gOFollow->pos.y - pos.y) > (int)(wP.height * 0.8))
		{
			pos.y += (int)(wP.height * 0.2);
		}
	}
}