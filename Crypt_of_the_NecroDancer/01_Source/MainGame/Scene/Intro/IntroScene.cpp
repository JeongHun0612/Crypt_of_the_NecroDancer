#include "Stdafx.h"
#include "IntroScene.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

HRESULT IntroScene::init()
{
	_hWndVideo = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOPLAYBAR, "Resources/Video/intro.wmv");

	MoveWindow(_hWndVideo, 0, 0, WINSIZE_X, WINSIZE_Y, FALSE);

	MCIWndPlay(_hWndVideo);

	return S_OK;
}

void IntroScene::release()
{
	MCIWndClose(_hWndVideo);
	MCIWndDestroy(_hWndVideo);
}

void IntroScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || MCIWndGetLength(_hWndVideo) <= MCIWndGetPosition(_hWndVideo))
	{
		SCENEMANAGER->changeScene("title");
	}
}

void IntroScene::render()
{
	// ! Do Noting
}
