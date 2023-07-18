#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	SOUNDMANAGER->play("stage1-1", 0.5f);

	// 플레이어 초기화
	PLAYER->init();
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	// 비트 초기화
	BEAT->init();

	_nextIdxY = PLAYER->getPosIdxY();
	_nextIdxX = PLAYER->getPosIdxX();
	_nextDirection = PLAYER->getCurDirection();

	// UI 초기화
	UIMANAGER->init();

    return S_OK;
}

void GameScene::release(void)
{
	SOUNDMANAGER->stop("stage1-1");
}

void GameScene::update(void)
{
	CAMERA->update();
	PLAYER->update();
	BEAT->update();
}

void GameScene::render(void)
{
	// 플레이어 출력
	PLAYER->render(getMemDC());

	// 비트 출력
	BEAT->render(getMemDC());

	// UI 출력
	UIMANAGER->render(getMemDC());
}
