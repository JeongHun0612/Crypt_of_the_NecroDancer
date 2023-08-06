#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	_padeAlpha = 0;

	return S_OK;
}

void GameScene::release(void)
{
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		delete(*iter);
		iter = _vEnemy.erase(iter);
	}

	for (auto iter = _vItem.begin(); iter != _vItem.end(); ++iter)
	{
		delete(*iter);
		iter = _vItem.erase(iter);
	}

	_vEnemy.clear();
	_vItem.clear();
}

void GameScene::update(void)
{
	// 카메라 업데이트
	CAMERA->update();

	// 비트 업데이트
	BEAT->update();

	// 타일 업데이트
	TILEMAP->update();

	// 아이템 업데이트
	for (auto iter = TILEMAP->getItemList().begin(); iter != TILEMAP->getItemList().end();)
	{
		(*iter)->update();

		if ((*iter)->getIsSale())
		{
			(*iter)->release();
			iter = TILEMAP->getItemList().erase(iter);
		}
		else ++iter;
	}

	// 플레이어 업데이트
	if (PLAYER->getCurHP() > 0)
	{
		PLAYER->update();
	}

	// 애너미 업데이트
	for (int i = 0; i < TILEMAP->getEnemyList().size(); i++)
	{
		Enemy* curEnemy = TILEMAP->getEnemyList()[i];
		curEnemy->update();

		if (curEnemy->getCurHP() <= 0)
		{
			curEnemy->release();
			TILEMAP->getEnemyList().erase(TILEMAP->getEnemyList().begin() + i);
		}
	}

	// UI 업데이트
	UIMANAGER->update();

	// 노래 끝날 시 다음 씬으로 변경
	if (!BEAT->getIsMusic())
	{
		if (_padeAlpha < 255)
		{
			_padeAlpha += 2;

			if (_padeAlpha == 20)
			{
				IMAGEMANAGER->findImage("trap_door")->setFrameX(1);
				SOUNDMANAGER->play("trap_door_open");
				SOUNDMANAGER->play("trap_door");
			}

			if (_padeAlpha >= 20)
			{
				PLAYER->setPos(PLAYER->getPos().x, PLAYER->getPos().y + 1.0f);
				PLAYER->setPlayerAlpha(PLAYER->getPlayerAlpha() - 15);
				PLAYER->setShadowAlpha(0);

				if (PLAYER->getPlayerAlpha() <= 0)
				{
					PLAYER->setPlayerAlpha(0);
				}
			}

			if (_padeAlpha > 255)
			{
				_padeAlpha = 255;
			}
		}
	}

	// 플레이어 사망 시
	if (PLAYER->getCurHP() <= 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			PLAYER->release();
			SCENEMANAGER->changeScene("lobby");
		}
	}
}

void GameScene::render(void)
{
	// 타일 출력
	TILEMAP->render(getMemDC());

	// 아이템 출력
	for (auto iter = TILEMAP->getItemList().begin(); iter != TILEMAP->getItemList().end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// 플레이어 출력
	if (PLAYER->getCurHP() > 0)
	{
		PLAYER->render(getMemDC());
	}

	// 몬스터 출력
	for (auto iter = TILEMAP->getEnemyList().begin(); iter != TILEMAP->getEnemyList().end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// 비트 출력
	BEAT->render(getMemDC());

	// UI 출력
	UIMANAGER->render(getMemDC());

	// 노래 끝 애니메이션 출력
	if (!BEAT->getIsMusic())
	{
		// 문 함정
		IMAGEMANAGER->findImage("trap_door")->frameRender(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("trap_door")->getFrameWidth() / 2,
			WINSIZE_Y_HALF - IMAGEMANAGER->findImage("trap_door")->getFrameHeight() / 2,
			IMAGEMANAGER->findImage("trap_door")->getFrameX(), 0);

		// 페이드 인 / 아웃
		IMAGEMANAGER->findImage("fade_effect")->alphaRender(getMemDC(), _padeAlpha);

		// 노래 끝 텍스트
		IMAGEMANAGER->findImage("text_songend")->render(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("text_songend")->getWidth() / 2,
			200);
	}

	// 플레이어 사망 시 출력
	if (PLAYER->getCurHP() <= 0)
	{
		IMAGEMANAGER->findImage("text_death")->render(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("text_death")->getWidth() / 2,
			WINSIZE_Y_HALF + 150);
	}
}