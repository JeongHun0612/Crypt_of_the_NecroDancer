#pragma once
#include "SingletonBase.h"

#define TILE_COL_CNT		21
#define TILE_ROW_CNT		13

class Camera : public SingletonBase<Camera>
{
private:
	POINTFLOAT _pos;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	POINTFLOAT getPos() { return _pos; }
};