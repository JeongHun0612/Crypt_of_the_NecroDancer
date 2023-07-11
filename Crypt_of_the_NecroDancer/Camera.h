#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINT _lookPos;
	POINT _lookPosIdx;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);


	POINT getLookPos() { return _lookPos; }
	void setLookPos(int x, int y) { _lookPos = { x, y }; }

	POINT getLookPosIdx() { return _lookPosIdx; }
	void setLookPosIdx(int x, int y) { _lookPosIdx = { x, y }; }
};

