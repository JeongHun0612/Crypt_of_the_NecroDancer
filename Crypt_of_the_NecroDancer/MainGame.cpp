#include "Stdafx.h"
#include "MainGame.h"

#include "TitleScene.h"
#include "LobbyScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// �̹��� �߰�
	addImage();

	// ���� �߰�
	addSound();

	// �� �߰�
	SCENEMANAGER->addScene("title", new TitleScene);			// Ÿ��Ʋ
	SCENEMANAGER->addScene("lobby", new LobbyScene);			// �κ�

	SCENEMANAGER->changeScene("lobby");


	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// =====================================================================

	// ���� �� ���
	SCENEMANAGER->render();

	// �ð� Ȯ�� (������, ���� Ÿ��, ��Ÿ Ÿ��)
	TIMEMANAGER->render(getMemDC());

	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void MainGame::addImage()
{
	//char path[128] = "../Resources/";
	//strcat_s(path, sizeof(path), "Images/UI/Title.bmp");
	//cout << path << endl;

	// Ÿ��Ʋ ȭ��
	IMAGEMANAGER->addImage("title", "Resources/Images/UI/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("anykey", "Resources/Images/UI/Anykey.bmp", WINSIZE_X / 3, WINSIZE_Y / 15, true, RGB(255, 0, 255));

	// Ÿ��
	IMAGEMANAGER->addImage("tile_terrain", "Resources/Images/Tile/Tile_Terrain.bmp", 512, 128, true, RGB(255, 0 ,255));

	// HUD
	IMAGEMANAGER->addFrameImage("beat_heart", "Resources/Images/HUD/BeatHeart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar1", "Resources/Images/HUD/BeatBar1.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar2", "Resources/Images/HUD/BeatBar2.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar3", "Resources/Images/HUD/BeatBar3.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("missed", "Resources/Images/HUD/Missed.bmp", 72, 26, true, RGB(255, 0, 255));

	// �÷��̾�
	IMAGEMANAGER->addFrameImage("player_head", "Resources/Images/Player/Head.bmp", 244, 44, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body", "Resources/Images/Player/Body.bmp", 272, 300, 8, 10, true, RGB(255, 0, 255));

	// ���� - ������
	IMAGEMANAGER->addFrameImage("slime_green", "Resources/Images/Enemy/Slime/Slime_Green.bmp", 208, 208, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slime_blue", "Resources/Images/Enemy/Slime/Slime_Blue.bmp", 416, 208, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slime_yellow", "Resources/Images/Enemy/Slime/Slime_Yellow.bmp", 208, 208, 4, 4, true, RGB(255, 0, 255));
}

void MainGame::addSound()
{
	// BGM
	SOUNDMANAGER->addSound("title", "Resources/Sounds/BGM/title.mp3", true, false);
	SOUNDMANAGER->addSound("stage1-1", "Resources/Sounds/BGM/stage1-1.mp3", true, false);
}
