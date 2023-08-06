#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// Ÿ�� �ʱ�ȭ
	TILEMAP->init(0);

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(6, 3, TILEMAP->getTiles());

	// ��Ʈ �ʱ�ȭ
	BEAT->init();
	BEAT->setIsBeat(true);

	// UI �ʱ�ȭ
	UIMANAGER->init();

	// ���� �÷���
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

	// ���� ��������
	if (TILEMAP->getIsNextStage())
	{
		SCENEMANAGER->changeScene("stage1_1");
	}
}

void LobbyScene::render()
{
	// Ÿ�� ���
	TILEMAP->render(getMemDC());

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());
}