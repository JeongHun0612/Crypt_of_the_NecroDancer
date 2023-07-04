#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

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
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	
	// render
	RectangleMakeCenter(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	this->getBackBuffer()->render(getHDC(), 0, 0);
}
