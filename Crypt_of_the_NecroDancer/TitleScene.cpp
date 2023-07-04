#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	IMAGEMANAGER->addImage("title", "Images/UI/title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("anykey", "Images/UI/anykey.bmp", WINSIZE_X / 3, WINSIZE_Y / 15, true, RGB(255, 0, 255));

	_title = IMAGEMANAGER->findImage("title");
	_anyKey = IMAGEMANAGER->findImage("anykey");

	return S_OK;
}

void TitleScene::release()
{
}

void TitleScene::update()
{

}

void TitleScene::render()
{
	_title->render(getMemDC());
	_anyKey->render(getMemDC(), WINSIZE_X / 2 - (_anyKey->getWidth() / 2), WINSIZE_Y - 70);
}
