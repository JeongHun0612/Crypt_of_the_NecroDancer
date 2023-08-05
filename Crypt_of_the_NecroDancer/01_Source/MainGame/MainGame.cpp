#include "../2DFrameWork/PCH/Stdafx.h"
#include "MainGame.h"

#include "../MainGame/Scene/Intro/IntroScene.h"
#include "../MainGame/Scene/Title/TitleScene.h"
#include "../MainGame/Scene/Lobby/LobbyScene.h"
#include "../MainGame/Scene/Stage/Stage1_1Scene.h"
#include "../MainGame/Scene/Stage/Stage1_2Scene.h"
#include "../MainGame/Scene/Stage/Boss_Scene.h"

#include "../MainGame/Scene/TestScene/TestScene.h"


HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 이미지 추가
	initImage();

	// 사운드 추가
	initSound();

	// 싱글톤 클래스 초기화
	BEAT->init();
	CAMERA->init();
	PLAYER->init();

	// 씬 추가
	SCENEMANAGER->addScene("intro", new IntroScene);			// 인트로
	SCENEMANAGER->addScene("title", new TitleScene);			// 타이틀
	SCENEMANAGER->addScene("lobby", new LobbyScene);			// 로비
	SCENEMANAGER->addScene("stage1_1", new Stage1_1Scene);		// 스테이지1-1
	SCENEMANAGER->addScene("stage1_2", new Stage1_2Scene);		// 스테이지1-2
	SCENEMANAGER->addScene("boss", new Boss_Scene);				// 보스

	SCENEMANAGER->addScene("test", new TestScene);		// 테스트

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
	IMAGEMANAGER->addImage("title", "02_Resources/Images/UI/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("anykey", "02_Resources/Images/UI/Anykey.bmp", WINSIZE_X / 3, WINSIZE_Y / 15, true, RGB(255, 0, 255));

	// ===================
	// Text
	// ===================
	IMAGEMANAGER->addImage("text_songend", "02_Resources/Images/Text/songend.bmp", 400, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("text_death", "02_Resources/Images/Text/death.bmp", 700, 50, true, RGB(255, 0, 255));


	// ===================
	// 타일
	// ===================
	IMAGEMANAGER->addFrameImage("tile_terrain", "02_Resources/Images/Tile/Tile_Terrain.bmp", 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile_wall", "02_Resources/Images/Tile/Tile_Wall.bmp", 320, 1152, 5, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile_torch", "02_Resources/Images/Tile/Tile_Torch.bmp", 96, 52, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trap_door", "02_Resources/Images/Tile/Trap_Door.bmp", 92, 36, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tile_audio", "02_Resources/Images/Tile/Tile_Audio.bmp", 448, 128, true, RGB(255, 0, 255));

	// ===================
	// HUD
	// ===================
	// HUD - Beat
	IMAGEMANAGER->addFrameImage("beat_heart", "02_Resources/Images/HUD/BeatHeart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beat_bar", "02_Resources/Images/HUD/BeatBar.bmp", 36, 60, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("missed", "02_Resources/Images/HUD/Missed.bmp", 72, 26, true, RGB(255, 0, 255));

	// HUD - Slot
	IMAGEMANAGER->addImage("slot_shovel", "02_Resources/Images/HUD/Slot_Shovel.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_attack", "02_Resources/Images/HUD/Slot_Attack.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_body", "02_Resources/Images/HUD/Slot_Body.bmp", 60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_item", "02_Resources/Images/HUD/Slot_Item2.bmp", 60, 76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_bomb", "02_Resources/Images/HUD/Slot_Bomb2.bmp", 60, 76, true, RGB(255, 0, 255));

	// HUD - HP
	IMAGEMANAGER->addFrameImage("small_heart", "02_Resources/Images/HUD/small_heart.bmp", 48, 22, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart", "02_Resources/Images/HUD/heart.bmp", 144, 44, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_full", "02_Resources/Images/HUD/heart_full.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_half", "02_Resources/Images/HUD/heart_half.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_null", "02_Resources/Images/HUD/heart_null.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));

	// HUD - Coin / Diamond
	IMAGEMANAGER->addImage("coin", "02_Resources/Images/HUD/coin.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("diamond", "02_Resources/Images/HUD/diamond.bmp", 50, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x_button", "02_Resources/Images/HUD/x_button.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "02_Resources/Images/HUD/number.bmp", 120, 18, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("small_number", "02_Resources/Images/HUD/number.bmp", 80, 12, 10, 1, true, RGB(255, 0, 255));

	// ===================
	// 플레이어
	// ===================
	IMAGEMANAGER->addFrameImage("player_head", "02_Resources/Images/Player/Head.bmp", 132, 52, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body", "02_Resources/Images/Player/Body.bmp", 160, 720, 4, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadow_standard", "02_Resources/Images/Player/shadow_standard.bmp", 48, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadow_large", "02_Resources/Images/Player/shadow_standard.bmp", 72, 81, true, RGB(255, 0, 255));


	// ===================
	// 아이템
	// ===================
	IMAGEMANAGER->addFrameImage("armor", "02_Resources/Images/Item/Armor.bmp", 240, 90, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("weapon", "02_Resources/Images/Item/Weapon.bmp", 144, 100, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovel", "02_Resources/Images/Item/Shovel.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("potion", "02_Resources/Images/Item/Food.bmp", 120, 80, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bomb", "02_Resources/Images/Item/Bomb.bmp", 240, 96, 5, 2, true, RGB(255, 0, 255));

	// 아이템 - 코인
	IMAGEMANAGER->addFrameImage("coin2", "02_Resources/Images/Item/Coin/coin2.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin3", "02_Resources/Images/Item/Coin/coin3.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin4", "02_Resources/Images/Item/Coin/coin4.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin5", "02_Resources/Images/Item/Coin/coin5.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin6", "02_Resources/Images/Item/Coin/coin6.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin7", "02_Resources/Images/Item/Coin/coin7.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin8", "02_Resources/Images/Item/Coin/coin8.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin9", "02_Resources/Images/Item/Coin/coin9.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin10", "02_Resources/Images/Item/Coin/coin10.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin_hoard", "02_Resources/Images/Item/Coin/coin_hoard.bmp", 68, 76, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin_hoard_middle", "02_Resources/Images/Item/Coin/coin_hoard_middle.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin_hoard_small", "02_Resources/Images/Item/Coin/coin_hoard_small.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));

	// ===================
	// Effect
	// ===================
	IMAGEMANAGER->addFrameImage("effect_dagger", "02_Resources/Images/Effect/effect_dagger.bmp", 144, 192, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy_effect", "02_Resources/Images/Effect/enemy_effect.bmp", 240, 44, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("effect_explosion", "02_Resources/Images/Effect/effect_explosion.bmp", 1536, 192, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hit_effect", "02_Resources/Images/Effect/hit_effect.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("fade_effect", "02_Resources/Images/Effect/fade_effect.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("dragon_fire", "02_Resources/Images/Effect/dragon_fire.bmp", 448, 48, 7, 1, true, RGB(255, 0, 255));


	// ===================
	// 몬스터 - 일반 몬스터
	// ===================
	// 몬스터 - 슬라임
	IMAGEMANAGER->addFrameImage("slime_green", "02_Resources/Images/Enemy/Slime/Slime_Green.bmp", 208, 208, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slime_blue", "02_Resources/Images/Enemy/Slime/Slime_Blue.bmp", 416, 208, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slime_orange", "02_Resources/Images/Enemy/Slime/Slime_Orange.bmp", 208, 208, 4, 4, true, RGB(255, 0, 255));

	// 몬스터 - 스켈레톤
	IMAGEMANAGER->addFrameImage("skeleton_normal", "02_Resources/Images/Enemy/Skeleton/Skeleton_normal.bmp", 416, 416, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skeleton_black", "02_Resources/Images/Enemy/Skeleton/Skeleton_black.bmp", 468, 416, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skeleton_yellow", "02_Resources/Images/Enemy/Skeleton/Skeleton_yellow.bmp", 468, 416, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skeleton_black_head", "02_Resources/Images/Enemy/Skeleton/Skeleton_black_head.bmp", 18, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skeleton_yellow_head", "02_Resources/Images/Enemy/Skeleton/Skeleton_yellow_head.bmp", 18, 18, true, RGB(255, 0, 255));

	// 몬스터 - 좀비
	IMAGEMANAGER->addFrameImage("zombie", "02_Resources/Images/Enemy/Zombie/Zombie.bmp", 384, 200, 8, 4, true, RGB(255, 0, 255));

	// 몬스터 - 박쥐
	IMAGEMANAGER->addFrameImage("bat_blue", "02_Resources/Images/Enemy/Bat/Bat_Blue.bmp", 192, 192, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_red", "02_Resources/Images/Enemy/Bat/Bat_Red.bmp", 192, 192, 4, 4, true, RGB(255, 0, 255));

	// 몬스터 - 원숭이
	IMAGEMANAGER->addFrameImage("monkey_normal", "02_Resources/Images/Enemy/Monkey/Monkey_Normal.bmp", 300, 192, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monkey_white", "02_Resources/Images/Enemy/Monkey/Monkey_White.bmp", 300, 192, 6, 4, true, RGB(255, 0, 255));

	// 몬스터 - 유령
	IMAGEMANAGER->addFrameImage("ghost", "02_Resources/Images/Enemy/Ghost/Ghost.bmp", 96, 192, 2, 4, true, RGB(255, 0, 255));


	// ===================
	// 몬스터 - 미니 보스 
	// ===================

	// 미니보스 - 미노타우로스
	IMAGEMANAGER->addFrameImage("minotaur", "02_Resources/Images/Enemy/Minotaur/Minotaur.bmp", 900, 392, 9, 4, true, RGB(255, 0, 255));

	// 미니보스 - 드래곤
	IMAGEMANAGER->addFrameImage("dragon_red", "02_Resources/Images/Enemy/Dragon/Dragon_Red.bmp", 1098, 408, 9, 4, true, RGB(255, 0, 255));

	// ===================
	// 몬스터 - 보스 
	// ===================

	// 보스 - 네크로댄서
	IMAGEMANAGER->addImage("necrodancer_cutScene", "02_Resources/Images/Enemy/NecroDancer/NecroDancer_CutScene.bmp", WINSIZE_X, 560, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cutScene_bar1", "02_Resources/Images/Enemy/NecroDancer/CutScene_Bar1.bmp", 800, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cutScene_bar2", "02_Resources/Images/Enemy/NecroDancer/CutScene_Bar2.bmp", 960, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("necrodancer", "02_Resources/Images/Enemy/NecroDancer/NecroDancer.bmp", 574, 92, 7, 1, true, RGB(255, 0, 255));


	// ===================
	// 몬스터 - NPC 
	// ===================

	// 상점 주인
	IMAGEMANAGER->addFrameImage("shopkeeper", "02_Resources/Images/Enemy/NPC/ShopKeeper.bmp", 752, 152, 8, 2, true, RGB(255, 0, 255));
}

void MainGame::initSound()
{
	// ===================
	// BGM
	// ===================
	SOUNDMANAGER->addSound("title", "02_Resources/Sounds/BGM/title.ogg", true, true);
	SOUNDMANAGER->addSound("lobby", "02_Resources/Sounds/BGM/lobby.ogg", true, true);
	SOUNDMANAGER->addSound("stage1_1", "02_Resources/Sounds/BGM/stage1_1.ogg", true, false);
	SOUNDMANAGER->addSound("stage1_1_shopkeeper", "02_Resources/Sounds/BGM/stage1_1_shopkeeper.ogg", true, false);
	SOUNDMANAGER->addSound("stage1_2", "02_Resources/Sounds/BGM/stage1_2.ogg", true, false);
	SOUNDMANAGER->addSound("stage1_2_shopkeeper", "02_Resources/Sounds/BGM/stage1_2_shopkeeper.ogg", true, false);
	SOUNDMANAGER->addSound("stage1_3", "02_Resources/Sounds/BGM/stage1_3.ogg", true, false);
	SOUNDMANAGER->addSound("stage1_3_shopkeeper", "02_Resources/Sounds/BGM/stage1_3_shopkeeper.ogg", true, false);
	SOUNDMANAGER->addSound("stage_boss", "02_Resources/Sounds/BGM/stage_boss.ogg", true, false);

	// ===================
	// 플레이어
	// ===================

	// 플레이어 - 삽질
	SOUNDMANAGER->addSound("dig1", "02_Resources/Sounds/Player/Dig/vo_cad_dig_01.wav", false, false);
	SOUNDMANAGER->addSound("dig2", "02_Resources/Sounds/Player/Dig/vo_cad_dig_02.wav", false, false);
	SOUNDMANAGER->addSound("dig3", "02_Resources/Sounds/Player/Dig/vo_cad_dig_03.wav", false, false);
	SOUNDMANAGER->addSound("dig4", "02_Resources/Sounds/Player/Dig/vo_cad_dig_04.wav", false, false);
	SOUNDMANAGER->addSound("dig5", "02_Resources/Sounds/Player/Dig/vo_cad_dig_05.wav", false, false);
	SOUNDMANAGER->addSound("dig6", "02_Resources/Sounds/Player/Dig/vo_cad_dig_06.wav", false, false);

	// 플레이어 - 난투
	SOUNDMANAGER->addSound("melee1_1", "02_Resources/Sounds/Player/Melee/vo_cad_melee_1_01.wav", false, false);
	SOUNDMANAGER->addSound("melee1_2", "02_Resources/Sounds/Player/Melee/vo_cad_melee_1_02.wav", false, false);
	SOUNDMANAGER->addSound("melee1_3", "02_Resources/Sounds/Player/Melee/vo_cad_melee_1_03.wav", false, false);
	SOUNDMANAGER->addSound("melee1_4", "02_Resources/Sounds/Player/Melee/vo_cad_melee_1_04.wav", false, false);

	// 플레이어 - 피격
	SOUNDMANAGER->addSound("hurt1", "02_Resources/Sounds/Player/Hurt/vo_cad_hurt_01.wav", false, false);
	SOUNDMANAGER->addSound("hurt2", "02_Resources/Sounds/Player/Hurt/vo_cad_hurt_02.wav", false, false);
	SOUNDMANAGER->addSound("hurt3", "02_Resources/Sounds/Player/Hurt/vo_cad_hurt_03.wav", false, false);
	SOUNDMANAGER->addSound("hurt4", "02_Resources/Sounds/Player/Hurt/vo_cad_hurt_04.wav", false, false);
	
	// 플레이어 - 죽음
	SOUNDMANAGER->addSound("death", "02_Resources/Sounds/Player/Death/vo_cad_death_01.wav", false, false);

	// 플레이어 - 함정
	SOUNDMANAGER->addSound("trap_door", "02_Resources/Sounds/Player/Trap/vo_cad_trapdoor_01.wav", false, false);


	// ===================
	// 애너미
	// ===================

	// 슬라임
	SOUNDMANAGER->addSound("slime_attack", "02_Resources/Sounds/Enemy/Slime/en_slime_attack.wav", false, false);
	SOUNDMANAGER->addSound("slime_hit", "02_Resources/Sounds/Enemy/Slime/en_slime_hit.wav", false, false);
	SOUNDMANAGER->addSound("slime_death", "02_Resources/Sounds/Enemy/Slime/en_slime_death_01.wav", false, false);

	// 스켈레톤
	SOUNDMANAGER->addSound("skeleton_attack", "02_Resources/Sounds/Enemy/Skeleton/en_skel_attack_melee.wav", false, false);
	SOUNDMANAGER->addSound("skeleton_hit", "02_Resources/Sounds/Enemy/Skeleton/en_skel_hit.wav", false, false);
	SOUNDMANAGER->addSound("skeleton_death", "02_Resources/Sounds/Enemy/Skeleton/en_skel_death.wav", false, false);

	// 박쥐
	SOUNDMANAGER->addSound("bat_attack", "02_Resources/Sounds/Enemy/Bat/en_bat_attack.wav", false, false);
	SOUNDMANAGER->addSound("bat_hit", "02_Resources/Sounds/Enemy/Bat/en_bat_hit.wav", false, false);
	SOUNDMANAGER->addSound("bat_death", "02_Resources/Sounds/Enemy/Bat/en_bat_death.wav", false, false);

	// 원숭이
	SOUNDMANAGER->addSound("monkey_hit", "02_Resources/Sounds/Enemy/Monkey/en_monkey_hit_01.wav", false, false);
	SOUNDMANAGER->addSound("monkey_grab", "02_Resources/Sounds/Enemy/Monkey/en_monkey_grab.wav", false, false);

	// 고스트
	SOUNDMANAGER->addSound("ghost_attack", "02_Resources/Sounds/Enemy/Ghost/en_ghost_attack.wav", false, false);
	SOUNDMANAGER->addSound("ghost_death", "02_Resources/Sounds/Enemy/Ghost/en_ghost_death.wav", false, false);

	// 미노타우로스
	SOUNDMANAGER->addSound("minotaur_attack", "02_Resources/Sounds/Enemy/Minotaur/en_minotaur_attack.wav", false, false);
	SOUNDMANAGER->addSound("minotaur_cry", "02_Resources/Sounds/Enemy/Minotaur/en_minotaur_cry.wav", false, false);
	SOUNDMANAGER->addSound("minotaur_charge", "02_Resources/Sounds/Enemy/Minotaur/en_minotaur_charge.wav", false, false);
	SOUNDMANAGER->addSound("minotaur_hit", "02_Resources/Sounds/Enemy/Minotaur/en_minotaur_hit_02.wav", false, false);
	SOUNDMANAGER->addSound("minotaur_death", "02_Resources/Sounds/Enemy/Minotaur/en_minotaur_death.wav", false, false);
	SOUNDMANAGER->addSound("minotaur_wallimpact", "02_Resources/Sounds/Enemy/Minotaur/en_minotaur_wallimpact.wav", false, false);

	// 드래곤
	SOUNDMANAGER->addSound("dargon_attack", "02_Resources/Sounds/Enemy/Dragon/en_dragon_attack_melee.wav", false, false);
	SOUNDMANAGER->addSound("dargon_prefire", "02_Resources/Sounds/Enemy/Dragon/en_dragon_attack_prefire.wav", false, false);
	SOUNDMANAGER->addSound("dargon_fire", "02_Resources/Sounds/Enemy/Dragon/en_dragon_attack_fire.wav", false, false);
	SOUNDMANAGER->addSound("dargon_cry", "02_Resources/Sounds/Enemy/Dragon/en_dragon_cry.wav", false, false);
	SOUNDMANAGER->addSound("dargon_hit", "02_Resources/Sounds/Enemy/Dragon/en_dragon_hit_01.wav", false, false);
	SOUNDMANAGER->addSound("dargon_death", "02_Resources/Sounds/Enemy/Dragon/en_dragon_death.wav", false, false);
	SOUNDMANAGER->addSound("dargon_walk", "02_Resources/Sounds/Enemy/Dragon/en_dragon_walk_01.wav", false, false);

	// 네크로댄서
	SOUNDMANAGER->addSound("necrodancer_rise", "02_Resources/Sounds/Enemy/NecroDancer/vo_nec_dia_rise_01.wav", false, false);
	SOUNDMANAGER->addSound("necrodancer_laugh", "02_Resources/Sounds/Enemy/NecroDancer/vo_nec_laugh_01.wav", false, false);
	SOUNDMANAGER->addSound("necrodancer_hurt", "02_Resources/Sounds/Enemy/NecroDancer/vo_nec_hurt_01.wav", false, false);
	SOUNDMANAGER->addSound("necrodancer_death", "02_Resources/Sounds/Enemy/NecroDancer/vo_nec_death.wav", false, false);



	// ===================
	// 오브젝트
	// ===================
	SOUNDMANAGER->addSound("dig_brick", "02_Resources/Sounds/Object/mov_dig_brick.wav", false, false);
	SOUNDMANAGER->addSound("dig_dirt", "02_Resources/Sounds/Object/mov_dig_dirt.wav", false, false);
	SOUNDMANAGER->addSound("dig_fail", "02_Resources/Sounds/Object/mov_dig_fail.wav", false, false);
	SOUNDMANAGER->addSound("dig_stone", "02_Resources/Sounds/Object/mov_dig_stone.wav", false, false);
	SOUNDMANAGER->addSound("create_break", "02_Resources/Sounds/Object/obj_crate_break.wav", false, false);
	SOUNDMANAGER->addSound("create_hit", "02_Resources/Sounds/Object/obj_crate_hit.wav", false, false);
	SOUNDMANAGER->addSound("door_open", "02_Resources/Sounds/Object/obj_door_open.wav", false, false);
	SOUNDMANAGER->addSound("trap_door_open", "02_Resources/Sounds/Object/obj_trap_trapdoor_open.wav", false, false);


	// ===================
	// SFX
	// ===================
	SOUNDMANAGER->addSound("boss_zone_open", "02_Resources/Sounds/SFX/boss_zone1_walls.wav", false, false);
	SOUNDMANAGER->addSound("player_hit_ST", "02_Resources/Sounds/SFX/sfx_player_hit_ST.wav", false, false);
	SOUNDMANAGER->addSound("missed_beat", "02_Resources/Sounds/SFX/sfx_missedbeat.wav", false, false);
	SOUNDMANAGER->addSound("pickup_gold", "02_Resources/Sounds/SFX/sfx_pickup_gold_01.wav", false, false);
	SOUNDMANAGER->addSound("pickup_purchase", "02_Resources/Sounds/SFX/sfx_pickup_purchase.wav", false, false);
	SOUNDMANAGER->addSound("pickup_armor", "02_Resources/Sounds/SFX/sfx_pickup_armor.wav", false, false);
	SOUNDMANAGER->addSound("pickup_weapon", "02_Resources/Sounds/SFX/sfx_pickup_weapon.wav", false, false);
	SOUNDMANAGER->addSound("pickup_general", "02_Resources/Sounds/SFX/sfx_pickup_general_ST.wav", false, false);
	SOUNDMANAGER->addSound("bomb_explode", "02_Resources/Sounds/SFX/sfx_bomb_explode.wav", false, false);
	SOUNDMANAGER->addSound("bomb_lit", "02_Resources/Sounds/SFX/sfx_bomb_lit.wav", false, false);
	SOUNDMANAGER->addSound("item_food", "02_Resources/Sounds/SFX/sfx_item_food.wav", false, false);

	// ===================
	// 아나운서
	// ===================
	SOUNDMANAGER->addSound("announcer_thenecrodancer", "02_Resources/Sounds/Announcer/vo_announcer_thenecrodancer.wav", false, false);
}
