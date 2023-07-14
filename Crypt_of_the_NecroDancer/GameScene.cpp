#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
    return S_OK;
}

void GameScene::release(void)
{
}

void GameScene::update(void)
{
	//if (!_player.getIsMove())
	//{
	//	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	//	{
	//		if (!BEAT->getBeat())
	//		{
	//			BEAT->setIsMissed(true);
	//		}
	//		else
	//		{
	//			BEAT->setIsSuccess(true);

	//			if (_wallTile[_player.getPosIdx().y][_player.getPosIdx().x - 1].isColiider)
	//			{
	//				cout << "條! 條!" << endl;
	//			}
	//			else
	//			{
	//				_player.setIsMove(true);
	//				_player.setDirection(PLAYER_DIRECTION::LEFT);
	//			}
	//		}
	//	}

	//	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	//	{
	//		if (!BEAT->getBeat())
	//		{
	//			BEAT->setIsMissed(true);
	//		}
	//		else
	//		{
	//			BEAT->setIsSuccess(true);

	//			if (_wallTile[_player.getPosIdx().y][_player.getPosIdx().x + 1].isColiider)
	//			{
	//				cout << "條! 條!" << endl;
	//			}
	//			else
	//			{
	//				_player.setIsMove(true);
	//				_player.setDirection(PLAYER_DIRECTION::RIGHT);
	//			}
	//		}
	//	}
	//	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	//	{
	//		if (!BEAT->getBeat())
	//		{
	//			BEAT->setIsMissed(true);
	//		}
	//		else
	//		{
	//			BEAT->setIsSuccess(true);

	//			if (_wallTile[_player.getPosIdx().y - 1][_player.getPosIdx().x].isColiider)
	//			{
	//				cout << "條! 條!" << endl;
	//			}
	//			else
	//			{
	//				_player.setIsMove(true);
	//				_player.setDirection(PLAYER_DIRECTION::UP);
	//			}
	//		}
	//	}
	//	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	//	{
	//		if (!BEAT->getBeat())
	//		{
	//			BEAT->setIsMissed(true);
	//		}
	//		else
	//		{
	//			BEAT->setIsSuccess(true);

	//			if (_wallTile[_player.getPosIdx().y + 1][_player.getPosIdx().x].isColiider)
	//			{
	//				cout << "條! 條!" << endl;
	//			}
	//			else
	//			{
	//				_player.setIsMove(true);
	//				_player.setDirection(PLAYER_DIRECTION::DOWN);
	//			}
	//		}
	//	}
	//}
}

void GameScene::render(void)
{
}
