#pragma once
#include "GameNode.h"

class TestCameraScene : public GameNode
{
public:
	struct Camera
	{
		POINTFLOAT posCT;
		POINTFLOAT posLT;
		POINTFLOAT prevPos;
		RECT rc;
	};
	struct Object
	{
		POINTFLOAT pos;
		POINTFLOAT prevPos;
		RECT rc;
	};

private:
	GImage* _bg;
	POINTFLOAT _cameraDiff;
	POINTFLOAT _mapPosLT;

	Camera _camera;
	Object _enemy;
	Object _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

