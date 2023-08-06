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
	// ī�޶� ������Ʈ
	CAMERA->update();

	// ��Ʈ ������Ʈ
	BEAT->update();

	// Ÿ�� ������Ʈ
	TILEMAP->update();

	// ������ ������Ʈ
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

	// �÷��̾� ������Ʈ
	if (PLAYER->getCurHP() > 0)
	{
		PLAYER->update();
	}

	// �ֳʹ� ������Ʈ
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

	// UI ������Ʈ
	UIMANAGER->update();

	// �뷡 ���� �� ���� ������ ����
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

	// �÷��̾� ��� ��
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
	// Ÿ�� ���
	TILEMAP->render(getMemDC());

	// ������ ���
	for (auto iter = TILEMAP->getItemList().begin(); iter != TILEMAP->getItemList().end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// �÷��̾� ���
	if (PLAYER->getCurHP() > 0)
	{
		PLAYER->render(getMemDC());
	}

	// ���� ���
	for (auto iter = TILEMAP->getEnemyList().begin(); iter != TILEMAP->getEnemyList().end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// ��Ʈ ���
	BEAT->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());

	// �뷡 �� �ִϸ��̼� ���
	if (!BEAT->getIsMusic())
	{
		// �� ����
		IMAGEMANAGER->findImage("trap_door")->frameRender(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("trap_door")->getFrameWidth() / 2,
			WINSIZE_Y_HALF - IMAGEMANAGER->findImage("trap_door")->getFrameHeight() / 2,
			IMAGEMANAGER->findImage("trap_door")->getFrameX(), 0);

		// ���̵� �� / �ƿ�
		IMAGEMANAGER->findImage("fade_effect")->alphaRender(getMemDC(), _padeAlpha);

		// �뷡 �� �ؽ�Ʈ
		IMAGEMANAGER->findImage("text_songend")->render(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("text_songend")->getWidth() / 2,
			200);
	}

	// �÷��̾� ��� �� ���
	if (PLAYER->getCurHP() <= 0)
	{
		IMAGEMANAGER->findImage("text_death")->render(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("text_death")->getWidth() / 2,
			WINSIZE_Y_HALF + 150);
	}
}