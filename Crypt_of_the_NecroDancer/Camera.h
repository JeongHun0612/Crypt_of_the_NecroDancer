#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINTFLOAT _pos;
	POINTFLOAT _prevPos;

	int _shakeCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }
	POINTFLOAT getPos() { return _pos; }

	void setShakeCount(int shakeCount) { _shakeCount = shakeCount; }
};