#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "EndingScene.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

HRESULT EndingScene::init()
{
	_hWndVideo = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOPLAYBAR, "02_Resources/Video/ending.wmv");

	MoveWindow(_hWndVideo, 0, 0, WINSIZE_X, WINSIZE_Y, FALSE);

	MCIWndPlay(_hWndVideo);

	return S_OK;
}

void EndingScene::release()
{
	MCIWndClose(_hWndVideo);
	MCIWndDestroy(_hWndVideo);
}

void EndingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || MCIWndGetLength(_hWndVideo) <= MCIWndGetPosition(_hWndVideo))
	{
		SCENEMANAGER->changeScene("title");
	}
}

void EndingScene::render()
{
}
