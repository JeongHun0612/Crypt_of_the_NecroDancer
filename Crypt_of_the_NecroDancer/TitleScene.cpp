#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	_title = IMAGEMANAGER->findImage("title");
	_anyKey = IMAGEMANAGER->findImage("anykey");

	return S_OK;
}

void TitleScene::release()
{
	_title->release();
	_anyKey->release();
}

void TitleScene::update()
{
}

void TitleScene::render()
{
	_title->render(getMemDC());
	_anyKey->render(getMemDC(), WINSIZE_X / 2 - (_anyKey->getWidth() / 2), WINSIZE_Y - 70);
}
