#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "../../Object/Enemy/Boss/NecroDancer.h"

#include "../../Object/Enemy/NormalMonster/Skeleton/Skeleton_Normal.h"
#include "../../Object/Enemy/NormalMonster/Skeleton/Skeleton_Yellow.h"
#include "../../Object/Enemy/NormalMonster/Skeleton/Skeleton_Black.h"
#include "../../Object/Enemy/MiniBoss/Minotaur/Minotaur_Normal.h"
#include "../../Object/Enemy/MiniBoss/Dragon/Dragon_Red.h"


#include "Boss_Scene.h"

HRESULT Boss_Scene::init(void)
{
	GameScene::init();

	_barImg1.img = IMAGEMANAGER->findImage("cutScene_bar1");
	_barImg1.pos.x = -_barImg1.img->getWidth();
	_barImg1.pos.y = 80;

	_barImg2.img = IMAGEMANAGER->findImage("cutScene_bar2");
	_barImg2.pos.x = WINSIZE_X;
	_barImg2.pos.y = 615;

	_cutSceneImg.img = IMAGEMANAGER->findImage("necrodancer_cutScene");
	_cutSceneImg.pos.x = WINSIZE_X;
	_cutSceneImg.pos.y = 40;

	// 타일 초기화
	FileManager::loadTileMapFile("Boss_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Boss_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	_vTiles.push_back(_vTerrainTile);
	_vTiles.push_back(_vWallTile);

	_tileMaxCol = MAX_BOSS_COL;
	_tileMaxRow = MAX_BOSS_ROW;

	// 애너미 초기화
	_necroDancer = new NecroDancer;
	_necroDancer->init(8, 8, _vTiles, _tileMaxCol);
	_vEnemy.push_back(_necroDancer);

	// 플레이어 초기화
	PLAYER->init(8, 22, _vEnemy, _vItem, _vTiles, _tileMaxCol);
	PLAYER->setLightPower(15);

	// 비트 초기화
	BEAT->init("stage_boss.txt", "stage_boss");

	// 사운드 출력
	SOUNDMANAGER->play("announcer_thenecrodancer");
	SOUNDMANAGER->play("stage_boss");

	_isCutScene = true;
	_isOpen = false;

	return S_OK;
}

void Boss_Scene::release(void)
{
	GameScene::release();

	SOUNDMANAGER->stop("stage_boss");
}

void Boss_Scene::update(void)
{
	GameScene::update();

	// 보스 컷씬 애니메이션
	if (_isCutScene)
	{
		if (_cutSceneImg.pos.x > 0)
		{
			_cutSceneImg.pos.x -= 80;
			_barImg1.pos.x += 50;
		}

		if (_cutSceneImg.pos.x == 0)
		{
			if (_barImg2.pos.x > 320)
			{
				_barImg2.pos.x -= 60;
			}

			if (KEYMANAGER->isAnyKeyDown())
			{
				_isCutScene = false;
			}
		}
	}
	else
	{
		if (_cutSceneImg.pos.x < WINSIZE_X)
		{
			_cutSceneImg.pos.x += 80;
			_barImg1.pos.x -= 50;
			_barImg2.pos.x += 60;
		}
	}

	// 보스 사망
	if (_necroDancer->getCurHP() <= 0)
	{
		int startTileNum = 6 * _tileMaxCol + 5;

		// 출구 열림
		for (int i = startTileNum; i < startTileNum + 7; i++)
		{
			_vWallTile[i]->_isCollider = false;
			_vWallTile[i]->_isExist = false;
		}

		// 남은 몬스터 삭제
		for (auto iter = _vEnemy.begin(); iter < _vEnemy.end(); ++iter)
		{
			(*iter)->setCurHP(0);
		}

		_necroDancer->setIsHit(false);
		_necroDancer->setIsSkill(false);
	}

	// 미니 보스 소환 스킬
	if (_necroDancer->getIsSkill() && _necroDancer->getSkillPattern() == SKILL_PATTERN::MINIBOSS_SUMMON)
	{
		switch (RND->getInt(2))
		{
		case 0:
			_summonEnemy = new Minotaur_Normal;
			break;
		case 1:
			_summonEnemy = new Dragon_Red;
			break;
		}

		int posIdxX = 8 - (8 - _necroDancer->getPosIdx().x) / 2;
		int posIdxY = 11 - (11 - _necroDancer->getPosIdx().y) / 2;
		_summonEnemy->init(posIdxX, posIdxY, _vTiles, _tileMaxCol);

		_vEnemy.push_back(_summonEnemy);
		PLAYER->getEnemyList().push_back(_summonEnemy);

		_necroDancer->setIsSkill(false);
	}

	// 보스 히트 시
	if (_necroDancer->getIsHit())
	{
		SOUNDMANAGER->play("necrodancer_hurt");

		for (int i = 0; i < 2; i++)
		{
			switch (RND->getInt(3))
			{
			case 0:
				_summonEnemy = new Skeleton_Normal;
				break;
			case 1:
				_summonEnemy = new Skeleton_Yellow;
				break;
			case 2:
				_summonEnemy = new Skeleton_Black;
				break;
			}

			int posIdxX = 8 - (8 - _necroDancer->getPosIdx().x) / 2 + i;
			int posIdxY = 11 - (11 - _necroDancer->getPosIdx().y) / 2 + i;
			_summonEnemy->init(posIdxX, posIdxY, _vTiles, _tileMaxCol);

			_vEnemy.push_back(_summonEnemy);
			PLAYER->getEnemyList().push_back(_summonEnemy);
		}

		_necroDancer->setPosIdx(8 + (8 - _necroDancer->getPosIdx().x), RND->getFromIntTo(7, 14));

		int curTileIdx = (_necroDancer->getPosIdx().y) * _tileMaxCol + _necroDancer->getPosIdx().x;
		_vTerrainTile[curTileIdx]->_isCollider = true;
		_necroDancer->setCurTileIdx(curTileIdx);

		_necroDancer->setIsHit(false);
	}


	// 보스 존 입구에 들어왔을 시 효과
	if (PLAYER->getPosIdx().y == 15 && !_isOpen)
	{
		int startTileNum = 16 * _tileMaxCol + 7;

		for (int i = startTileNum; i < startTileNum + 3; i++)
		{
			_vWallTile[i]->_frameX = 0;
			_vWallTile[i]->_frameY = 7;
			_vWallTile[i]->_isCollider = true;
			_vWallTile[i]->_isExist = true;
			_vWallTile[i]->_hardNess = 7;
			_vWallTile[i]->_wallType = WALL_TYPE::STEEL;
		}

		startTileNum = 12 * _tileMaxCol + 0;

		for (int i = startTileNum; i < _vTerrainTile.size(); i++)
		{
			_vTerrainTile[i]->_isLight = false;
			_vWallTile[i]->_isLight = false;
		}

		SOUNDMANAGER->play("boss_zone_open");
		_isOpen = true;
	}


	// 바닥 타일 타입이 계단일 시 씬 변경
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::OPEN_STAIR && PLAYER->getIsNextStage())
	{
		//SCENEMANAGER->changeScene("stage1_2");
	}
}

void Boss_Scene::render(void)
{
	// 오디오 타일
	if (_necroDancer->getCurHP() > 0)
	{
		IMAGEMANAGER->findImage("tile_audio")->render(getMemDC(),
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - 5) * 64),
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - 4) * 64) - 32);
	}

	GameScene::render();

	// 보스 컷씬
	if (!_isOpen)
	{
		_barImg1.img->render(getMemDC(), _barImg1.pos.x, _barImg1.pos.y);
		_barImg2.img->render(getMemDC(), _barImg2.pos.x, _barImg2.pos.y);

		_cutSceneImg.img->render(getMemDC(), _cutSceneImg.pos.x, _cutSceneImg.pos.y);
	}
}
