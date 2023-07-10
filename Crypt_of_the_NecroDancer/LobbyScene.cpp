#include "Stdafx.h"
#include "LobbyScene.h"

bool isTest = false;

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("stage1-1");

	BEAT->init();

	_player.init();

	_tile = IMAGEMANAGER->findImage("tile_terrain");

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
	for (int i = 0; i < 3481; i++)
	{
		if (isTest)
		{
			int sourX = (i % 2) * 64;
			_tile->render(getMemDC(), (i % 59) * 64, (i / 59) * 64, sourX, 0, 64, 64);
		}
		else
		{
			int sourX = (i % 2) * 64;
			_tile->render(getMemDC(), (i % 59) * 64, (i / 59) * 64, sourX, 0, 64, 64);
		}
	}


	// 비트 출력
	BEAT->render(getMemDC());
	
	// 플레이어 출력
	_player.render();
}
