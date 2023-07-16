#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINTFLOAT _pos;

	int _shakeCount;
	float _shake;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void cameraShake(int shakeCount);

	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }
	POINTFLOAT getPos() { return _pos; }
};