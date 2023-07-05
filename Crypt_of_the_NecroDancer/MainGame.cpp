#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// �� �߰�
	SCENEMANAGER->addScene("title", new TitleScene);
	SCENEMANAGER->addScene("lobby", new LobbyScene);

	SCENEMANAGER->changeScene("title");


	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// =====================================================================

	// ���� �� ���
	SCENEMANAGER->render();

	// �ð� Ȯ�� (������, ���� �ð�, ��Ÿ Ÿ��)
	TIMEMANAGER->render(getMemDC());

	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
