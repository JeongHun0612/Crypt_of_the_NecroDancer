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
	
	// �ð� Ȯ�� (������, ���� �ð�, ��Ÿ Ÿ��)
	TIMEMANAGER->render(getMemDC());

	// render
	DrawRectMake(getMemDC(), rc);


	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
