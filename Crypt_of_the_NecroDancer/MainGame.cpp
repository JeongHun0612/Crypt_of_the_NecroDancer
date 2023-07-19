#include "Stdafx.h"
#include "MainGame.h"

#include "IntroScene.h"
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
	SCENEMANAGER->addScene("intro", new IntroScene);			// 인트로
	SCENEMANAGER->addScene("title", new TitleScene);			// 타이틀
	SCENEMANAGER->addScene("lobby", new LobbyScene);			// 로비
	SCENEMANAGER->addScene("game", new GameScene);				// 인게임

	SCENEMANAGER->addScene("test", new TestScene);							// 테스트 씬
	SCENEMANAGER->addScene("testCamera", new TestCameraScene);				// 테스트 씬

	SCENEMANAGER->changeScene("game");

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
	if (SCENEMANAGER->getCurScene()->getName() != "intro")
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

	IMAGEMANAGER->addFrameImage("terrain1", "Resources/Images/Tile/Terrain_1.bmp", 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wall1", "Resources/Images/Tile/WallTile.bmp", 320, 1107, 5, 9, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("tile_torch", "Resources/Images/Tile/Tile_Torch.bmp", 96, 52, 4, 1, true, RGB(255, 0, 255));

	// ===================
	// HUD
	// ===================
	// HUD - Beat
	IMAGEMANAGER->addFrameImage("beat_heart", "Resources/Images/HUD/BeatHeart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beat_bar", "Resources/Images/HUD/BeatBar.bmp", 36, 60, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("missed", "Resources/Images/HUD/Missed.bmp", 72, 26, true, RGB(255, 0, 255));

	// HUD - Slot
	IMAGEMANAGER->addImage("slot_shovel", "Resources/Images/HUD/Slot_Shovel.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_attack", "Resources/Images/HUD/Slot_Attack.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_body", "Resources/Images/HUD/Slot_Body.bmp", 60, 66, true, RGB(255, 0, 255));

	// HUD - HP
	IMAGEMANAGER->addFrameImage("small_heart", "Resources/Images/HUD/small_heart.bmp", 48, 22, 2, 1, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("armor", "Resources/Images/Item/Armor.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));

	// 아이템 - 코인
	IMAGEMANAGER->addFrameImage("coin1", "Resources/Images/Item/Coin/coin1.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin2", "Resources/Images/Item/Coin/coin2.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin3", "Resources/Images/Item/Coin/coin3.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin4", "Resources/Images/Item/Coin/coin4.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));

	// ===================
	// Effect
	// ===================
	IMAGEMANAGER->addFrameImage("effect_dagger", "Resources/Images/Effect/effect_dagger.bmp", 144, 192, 3, 4, true, RGB(255, 0, 255));


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
	// ===================
	// BGM
	// ===================
	SOUNDMANAGER->addSound("title", "Resources/Sounds/BGM/title.mp3", true, true);
	SOUNDMANAGER->addSound("lobby", "Resources/Sounds/BGM/lobby.mp3", true, true);
	SOUNDMANAGER->addSound("stage1-1", "Resources/Sounds/BGM/stage1-1.mp3", true, false);

	// ===================
	// 플레이어
	// ===================

	// 플레이어 - 삽질
	SOUNDMANAGER->addSound("dig1", "Resources/Sounds/Player/Dig/vo_cad_dig_01.mp3", false, false);
	SOUNDMANAGER->addSound("dig2", "Resources/Sounds/Player/Dig/vo_cad_dig_02.mp3", false, false);
	SOUNDMANAGER->addSound("dig3", "Resources/Sounds/Player/Dig/vo_cad_dig_03.mp3", false, false);
	SOUNDMANAGER->addSound("dig4", "Resources/Sounds/Player/Dig/vo_cad_dig_04.mp3", false, false);
	SOUNDMANAGER->addSound("dig5", "Resources/Sounds/Player/Dig/vo_cad_dig_05.mp3", false, false);
	SOUNDMANAGER->addSound("dig6", "Resources/Sounds/Player/Dig/vo_cad_dig_06.mp3", false, false);

	// 플레이어 - 난투
	SOUNDMANAGER->addSound("melee1_1", "Resources/Sounds/Player/Melee/vo_cad_melee_1_01.mp3", false, false);
	SOUNDMANAGER->addSound("melee1_2", "Resources/Sounds/Player/Melee/vo_cad_melee_1_02.mp3", false, false);
	SOUNDMANAGER->addSound("melee1_3", "Resources/Sounds/Player/Melee/vo_cad_melee_1_03.mp3", false, false);
	SOUNDMANAGER->addSound("melee1_4", "Resources/Sounds/Player/Melee/vo_cad_melee_1_04.mp3", false, false);

	// 플레이어 - 피격
	SOUNDMANAGER->addSound("hurt1", "Resources/Sounds/Player/Hurt/vo_cad_hurt_01.mp3", false, false);
	SOUNDMANAGER->addSound("hurt2", "Resources/Sounds/Player/Hurt/vo_cad_hurt_02.mp3", false, false);
	SOUNDMANAGER->addSound("hurt3", "Resources/Sounds/Player/Hurt/vo_cad_hurt_03.mp3", false, false);
	SOUNDMANAGER->addSound("hurt4", "Resources/Sounds/Player/Hurt/vo_cad_hurt_04.mp3", false, false);
	SOUNDMANAGER->addSound("hurt5", "Resources/Sounds/Player/Hurt/vo_cad_hurt_05.mp3", false, false);
	SOUNDMANAGER->addSound("hurt6", "Resources/Sounds/Player/Hurt/vo_cad_hurt_06.mp3", false, false);


	// ===================
	// 오브젝트
	// ===================
	SOUNDMANAGER->addSound("dig_brick", "Resources/Sounds/Object/mov_dig_brick.mp3", false, false);
	SOUNDMANAGER->addSound("dig_dirt", "Resources/Sounds/Object/mov_dig_dirt.mp3", false, false);
	SOUNDMANAGER->addSound("dig_fail", "Resources/Sounds/Object/mov_dig_fail.mp3", false, false);
	SOUNDMANAGER->addSound("dig_stone", "Resources/Sounds/Object/mov_dig_stone.mp3", false, false);

}
