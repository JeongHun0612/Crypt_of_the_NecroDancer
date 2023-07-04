#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// =====================================================================
	
	// 시간 확인 (프레임, 월드 시간, 델타 타임)
	TIMEMANAGER->render(getMemDC());

	// render
	DrawRectMake(getMemDC(), rc);


	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
