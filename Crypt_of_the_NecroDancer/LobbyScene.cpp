#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	_beatBox.init();

	_player.init();

	SOUNDMANAGER->play("stage1-1");

	return S_OK;
}

void LobbyScene::release()
{
	SOUNDMANAGER->stop("stage1-1");
}

void LobbyScene::update()
{
	_beatBox.update();

	_player.update();

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		SCENEMANAGER->changeScene("title");
	}
}

void LobbyScene::render()
{
	_beatBox.render();

	_player.render();

	//for (auto iter = _vSlime.begin(); iter != _vSlime.end(); ++iter)
	//{
	//	iter->render();
	//}
}
