#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINTFLOAT _pos;

	int _shakeCount;
	float _shake;

	bool _isMove;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void cameraShake(int shakeCount);

	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }
	POINTFLOAT getPos() { return _pos; }

	void setMove(bool isMove) { _isMove = isMove; }
};