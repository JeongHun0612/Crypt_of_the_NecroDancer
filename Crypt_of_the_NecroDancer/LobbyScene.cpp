#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	_beatBox.init();

	_player.init();

	return S_OK;
}

void LobbyScene::release()
{
}

void LobbyScene::update()
{
	_beatBox.update();

	_player.update();
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
