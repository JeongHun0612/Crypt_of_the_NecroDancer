#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 씬 추가
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

	// 현재 씬 출력
	SCENEMANAGER->render();

	// 시간 확인 (프레임, 월드 시간, 델타 타임)
	TIMEMANAGER->render(getMemDC());

	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
