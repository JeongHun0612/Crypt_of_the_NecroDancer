#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "Stage1_1Scene.h"

HRESULT Stage1_1Scene::init(void)
{
	GameScene::init();

	// Ÿ�� �ʱ�ȭ
	TILEMAP->init(1);

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(13, 10, TILEMAP->getEnemyList(), TILEMAP->getItemList(), TILEMAP->getTiles(), TILEMAP->getTileMaxCol());

	// ��Ʈ �ʱ�ȭ
	BEAT->init("stage1_1.txt", "stage1_1");

	// ���� ���
	SOUNDMANAGER->play("stage1_1");
	SOUNDMANAGER->play("stage1_1_shopkeeper");

	return S_OK;
}

void Stage1_1Scene::release(void)
{
	GameScene::release();

	SOUNDMANAGER->stop("stage1_1");
	SOUNDMANAGER->stop("stage1_1_shopkeeper");
}

void Stage1_1Scene::update(void)
{
	GameScene::update();

	// ���� ��������
	if (TILEMAP->getIsNextStage() || _padeAlpha == 255)
	{
		SCENEMANAGER->changeScene("stage1_2");
	}
}

void Stage1_1Scene::render(void)
{
	GameScene::render();
}
