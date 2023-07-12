#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINTFLOAT _targetPos;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void setTargetPos(float x, float y) { _targetPos = { x, y }; }

	float getDiffX(float objPosX) { return objPosX - 640.f; }
	float getDiffY(float objPosY) { return objPosY - 400.f; }
};