#pragma once
#include "../DesingPattern/SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	Vec2_F _pos;
	Vec2_F _prevPos;

	int _shakeCount;
	float _cameraSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }
	Vec2_F getPos() { return _pos; }

	Vec2_F getPrevPos() { return _prevPos; }

	void setShakeCount(int shakeCount) { _shakeCount = shakeCount; }
};