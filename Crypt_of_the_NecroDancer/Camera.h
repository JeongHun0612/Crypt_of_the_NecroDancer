#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	float _posX;
	float _posY;
	float _moveSpeed;
	RECT _rc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
};

