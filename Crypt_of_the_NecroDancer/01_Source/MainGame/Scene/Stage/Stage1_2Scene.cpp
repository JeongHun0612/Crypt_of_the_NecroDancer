#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "Stage1_2Scene.h"

HRESULT Stage1_2Scene::init(void)
{
	GameScene::init();

	// Ÿ�� �ʱ�ȭ
	TILEMAP->init(2);

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(13, 5, TILEMAP->getEnemyList(), TILEMAP->getItemList(), TILEMAP->getTiles(), TILEMAP->getTileMaxCol());

	// ��Ʈ �ʱ�ȭ
	BEAT->init("stage1_2.txt", "stage1_2");

	// ���� ���
	SOUNDMANAGER->play("stage1_2");
	SOUNDMANAGER->play("stage1_2_shopkeeper");

	return S_OK;
}

void Stage1_2Scene::release(void)
{
	GameScene::release();

	SOUNDMANAGER->stop("stage1_2");
	SOUNDMANAGER->stop("stage1_2_shopkeeper");
}

void Stage1_2Scene::update(void)
{
	GameScene::update();

	// ���� ��������
	if (TILEMAP->getIsNextStage() || _padeAlpha == 255)
	{
		SCENEMANAGER->changeScene("boss");
	}
}

void Stage1_2Scene::render(void)
{
	GameScene::render();
}
