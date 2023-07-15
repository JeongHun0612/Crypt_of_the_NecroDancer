#include "Stdafx.h"
#include "MainGame.h"

#include "TitleScene.h"
#include "LobbyScene.h"
#include "GameScene.h"

#include "TestScene.h"
#include "TestCameraScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 이미지 추가
	initImage();

	// 사운드 추가
	initSound();

	// 씬 추가
	SCENEMANAGER->addScene("title", new TitleScene);			// 타이틀
	SCENEMANAGER->addScene("lobby", new LobbyScene);			// 로비
	SCENEMANAGER->addScene("game", new GameScene);				// 인게임

	SCENEMANAGER->addScene("test", new TestScene);							// 테스트 씬
	SCENEMANAGER->addScene("testCamera", new TestCameraScene);				// 테스트 씬

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

	// 글자 배경모드 - TRANSPARENT : 투명한
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	// 현재 씬 출력
	SCENEMANAGER->render();

	// 시간 확인 (프레임, 월드 타임, 델타 타임)
	TIMEMANAGER->render(getMemDC());

	// =====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void MainGame::initImage()
{
	// ===================
	// 타이틀 화면
	// ===================
	IMAGEMANAGER->addImage("title", "Resources/Images/UI/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("anykey", "Resources/Images/UI/Anykey.bmp", WINSIZE_X / 3, WINSIZE_Y / 15, true, RGB(255, 0, 255));

	// ===================
	// 타일
	// ===================
	IMAGEMANAGER->addImage("tile_terrain", "Resources/Images/Tile/Tile_Terrain.bmp", 512, 128, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("terrain1", "Resources/Images/Tile/Terrain_1.bmp", 128, 128, 2, 2, true, RGB(255, 0 ,255));
	IMAGEMANAGER->addFrameImage("wall1", "Resources/Images/Tile/WallTile.bmp", 320, 1107, 5, 9, true, RGB(255, 0, 255));

	// ===================
	// HUD
	// ===================
	// HUD - Beat
	IMAGEMANAGER->addFrameImage("beat_heart", "Resources/Images/HUD/BeatHeart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar1", "Resources/Images/HUD/BeatBar1.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar2", "Resources/Images/HUD/BeatBar2.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("beat_bar3", "Resources/Images/HUD/BeatBar3.bmp", 12, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("missed", "Resources/Images/HUD/Missed.bmp", 72, 26, true, RGB(255, 0, 255));

	// HUD - Slot
	IMAGEMANAGER->addImage("slot_shovel", "Resources/Images/HUD/Slot_Shovel.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_attack", "Resources/Images/HUD/Slot_Attack.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_body", "Resources/Images/HUD/Slot_Body.bmp", 60, 66, true, RGB(255, 0, 255));

	// HUD - HP
	IMAGEMANAGER->addFrameImage("heart", "Resources/Images/HUD/heart.bmp", 144, 44, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_full", "Resources/Images/HUD/heart_full.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_half", "Resources/Images/HUD/heart_half.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_null", "Resources/Images/HUD/heart_null.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));

	// HUD - Coin / Diamond
	IMAGEMANAGER->addImage("coin", "Resources/Images/HUD/coin.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("diamond", "Resources/Images/HUD/diamond.bmp", 50, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x_button", "Resources/Images/HUD/x_button.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "Resources/Images/HUD/number.bmp", 150, 17, 10, 1, true, RGB(255, 0, 255));



	// ===================
	// 플레이어
	// ===================
	IMAGEMANAGER->addFrameImage("player_head", "Resources/Images/Player/Head.bmp", 224, 44, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body", "Resources/Images/Player/Body.bmp", 272, 300, 8, 10, true, RGB(255, 0, 255));

	// ===================
	// 아이템
	// ===================
	IMAGEMANAGER->addFrameImage("shovel", "Resources/Images/Item/Shovel.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dagger", "Resources/Images/Item/Dagger.bmp", 26, 52, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword", "Resources/Images/Item/Sword.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));


	// ===================
	// 몬스터
	// ===================
	// 몬스터 - 슬라임
	IMAGEMANAGER->addFrameImage("slime_green", "Resources/Images/Enemy/Slime/Slime_Green.bmp", 208, 208, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slime_blue", "Resources/Images/Enemy/Slime/Slime_Blue.bmp", 416, 208, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slime_yellow", "Resources/Images/Enemy/Slime/Slime_Yellow.bmp", 208, 208, 4, 4, true, RGB(255, 0, 255));
}

void MainGame::initSound()
{
	// BGM
	SOUNDMANAGER->addSound("title", "Resources/Sounds/BGM/title.mp3", true, true);
	SOUNDMANAGER->addSound("lobby", "Resources/Sounds/BGM/lobby.mp3", true, true);
	SOUNDMANAGER->addSound("stage1-1", "Resources/Sounds/BGM/stage1-1.mp3", true, false);
}
