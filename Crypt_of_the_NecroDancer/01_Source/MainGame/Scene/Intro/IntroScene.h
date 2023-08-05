#pragma once
#include "../../../2DFrameWork/GameCore/GameNode.h"

class IntroScene : public GameNode
{
private:
	HWND _hWndVideo;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	IntroScene() {}
	~IntroScene() {}
};