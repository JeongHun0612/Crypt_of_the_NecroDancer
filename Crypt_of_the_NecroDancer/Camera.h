#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINTFLOAT _pos;
	RECT _rc;

	POINTFLOAT _targetPos;
	POINTFLOAT _prevTargetPos;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	RECT getCameraRect() { return _rc; }

	POINTFLOAT getTargetPos() { return _targetPos; }
	void setTargetPos(float x, float y) { _targetPos = { x, y }; }

	POINTFLOAT getPrevTargetPos() { return _prevTargetPos; }
	void setPrevTargetPos(float x, float y) { _prevTargetPos = { x, y }; }

	//float getDiffX(float objPosX) { return objPosX - 640.f; }
	//float getDiffY(float objPosY) { return objPosY - 400.f; }

	void callDiff();
};