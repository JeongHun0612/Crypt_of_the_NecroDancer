#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// 타일 초기화
	TILEMAP->init(0);

	// 플레이어 초기화
	PLAYER->init(6, 3, TILEMAP->getTiles());

	// 비트 초기화
	BEAT->init();
	BEAT->setIsBeat(true);

	// UI 초기화
	UIMANAGER->init();

	// 사운드 플레이
	SOUNDMANAGER->play("lobby");

	return S_OK;
}

void LobbyScene::release()
{
	SOUNDMANAGER->stop("lobby");
}

void LobbyScene::update()
{
	TILEMAP->update();

	CAMERA->update();

	PLAYER->update();

	// 다음 스테이지
	if (TILEMAP->getIsNextStage())
	{
		SCENEMANAGER->changeScene("stage1_1");
	}
}

void LobbyScene::render()
{
	// 타일 출력
	TILEMAP->render(getMemDC());

	// 플레이어 출력
	PLAYER->render(getMemDC());

	// UI 출력
	UIMANAGER->render(getMemDC());
}