#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	BEAT->init();
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
	BEAT->update();

	_player.update();
}

void LobbyScene::render()
{
	// 비트 출력
	BEAT->render(getMemDC());
	
	// 플레이어 출력
	_player.render();
}
