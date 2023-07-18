#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	SOUNDMANAGER->play("stage1-1", 0.5f);

	// �÷��̾� �ʱ�ȭ
	PLAYER->init();
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	// ��Ʈ �ʱ�ȭ
	BEAT->init();

	_nextIdxY = PLAYER->getPosIdxY();
	_nextIdxX = PLAYER->getPosIdxX();
	_nextDirection = PLAYER->getCurDirection();

	// UI �ʱ�ȭ
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
	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// ��Ʈ ���
	BEAT->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());
}
