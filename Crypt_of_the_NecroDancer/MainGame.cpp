#include "Stdafx.h"
#include "MainGame.h"

#include "TitleScene.h"
#include "LobbyScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 이미지 추가
	addImage();

	// 사운드 추가
	addSound();

	// 씬 추가
	SCENEMANAGER->addScene("title", new TitleScene);			// 타이틀
	SCENEMANAGER->addScene("lobby", new LobbyScene);			// 로비

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

	// 현재 씬 출력
	SCENEMANAGER->render();

	// 시간 확인 (프레임, 월드 타임, 델타 타임)
	TIMEMANAGER->render(getMemDC());

	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void MainGame::addImage()
{
	//char path[128] = "../Resources/";
	//strcat_s(path, sizeof(path), "Images/UI/Title.bmp");
	//cout << path << endl;

	// 타이틀 화면
	IMAGEMANAGER->addImage("title", "Resources/Images/UI/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("anykey", "Resources/Images/UI/Anykey.bmp", WINSIZE_X / 3, WINSIZE_Y / 15, true, RGB(255, 0, 255));

	// 타일
	IMAGEMANAGER->addImage("tile_terrain", "Resources/Images/Tile/Tile_Terrain.bmp", 512, 128, true, RGB(255, 0 ,255));

	// HUD
	IMAGEMANAGER->addFrameImage("beat_heart", "Resources/Images/HUD/BeatHeart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar1", "Resources/Images/HUD/BeatBar1.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar2", "Resources/Images/HUD/BeatBar2.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar3", "Resources/Images/HUD/BeatBar3.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("missed", "Resources/Images/HUD/Missed.bmp", 72, 26, true, RGB(255, 0, 255));

	// 플레이어
	IMAGEMANAGER->addFrameImage("player_head", "Resources/Images/Player/Head.bmp", 244, 44, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body", "Resources/Images/Player/Body.bmp", 272, 300, 8, 10, true, RGB(255, 0, 255));

	// 몬스터 - 슬라임
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
