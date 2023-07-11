#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	_title = IMAGEMANAGER->findImage("title");
	_anyKey = IMAGEMANAGER->findImage("anykey");

	SOUNDMANAGER->play("title");

	return S_OK;
}

void TitleScene::release()
{
	SOUNDMANAGER->stop("title");
}

void TitleScene::update()
{
	if (KEYMANAGER->isAnyKeyDown())
	{
		SCENEMANAGER->changeScene("lobby");
	}
}

void TitleScene::render()
{
	_title->render(getMemDC());
	_anyKey->render(getMemDC(), WINSIZE_X / 2 - (_anyKey->getWidth() / 2), WINSIZE_Y - 70);
}
