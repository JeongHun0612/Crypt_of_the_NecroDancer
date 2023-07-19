#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init(void)
{
	// 인벤토리 초기화
	Inventory shovelSlot;

	shovelSlot.img = IMAGEMANAGER->findImage("slot_shovel");
	shovelSlot.type = ITEM_TYPE::SHOVEL;
	shovelSlot.x = 10;
	shovelSlot.y = 10;

	_vInventory.push_back(shovelSlot);

	Inventory attackSlot;
	attackSlot.img = IMAGEMANAGER->findImage("slot_attack");
	attackSlot.type = ITEM_TYPE::ATTACK;
	attackSlot.x = 80;
	attackSlot.y = 10;

	_vInventory.push_back(attackSlot);

	Inventory bodySlot;
	bodySlot.img = IMAGEMANAGER->findImage("slot_body");
	bodySlot.type = ITEM_TYPE::BODY;
	bodySlot.x = 10;
	bodySlot.y = 80;

	_vInventory.push_back(bodySlot);


	// 하트 초기화
	for (int i = PLAYER->getMaxHP() / 2; i > 0; i--)
	{
		Heart heart;

		heart.img = IMAGEMANAGER->findImage("heart");
		heart.x = WINSIZE_X - 145 - (i * 55);
		heart.y = 10;

		_vHeart.push_back(heart);
	}

	return S_OK;
}

void UIManager::release(void)
{
}

void UIManager::update(void)
{

}

void UIManager::render(HDC hdc)
{
	// 인벤토리 출력
	for (auto iter = _vInventory.begin(); iter != _vInventory.end(); ++iter)
	{
		iter->img->render(hdc, iter->x, iter->y);
	}

	// HP 출력
	for (int i = 0; i < _vHeart.size(); i++)
	{
		_prevHP = PLAYER->getCurHP() - (i * 2);

		if (_prevHP > 1)
		{
			_vHeart[i].img->frameRender(hdc, _vHeart[i].x, _vHeart[i].y, 0, 0);
		}
		else if (_prevHP == 1)
		{
			_vHeart[i].img->frameRender(hdc, _vHeart[i].x, _vHeart[i].y, 1, 0);
		}
		else
		{
			_vHeart[i].img->frameRender(hdc, _vHeart[i].x, _vHeart[i].y, 2, 0);
		}
	}

	// 코인 / 다이아몬드
	IMAGEMANAGER->findImage("coin")->render(hdc, WINSIZE_X - 140, 15);
	IMAGEMANAGER->findImage("x_button")->render(hdc, WINSIZE_X - 90, 30);

	for (int i = 0; i < to_string(PLAYER->getCoin()).size(); i++)
	{
		IMAGEMANAGER->findImage("number")->frameRender(hdc, WINSIZE_X - 70 + (i * 15), 27, to_string(PLAYER->getCoin())[i] - 48, 0);
	}

	IMAGEMANAGER->findImage("diamond")->render(hdc, WINSIZE_X - 145, 65);
	IMAGEMANAGER->findImage("x_button")->render(hdc, WINSIZE_X - 90, 80);

	for (int i = 0; i < to_string(PLAYER->getDiamond()).size(); i++)
	{
		IMAGEMANAGER->findImage("number")->frameRender(hdc, WINSIZE_X - 70 + (i * 15), 77, to_string(PLAYER->getDiamond())[i] - 48, 0);
	}

	for (auto iter = _vCoin.begin(); iter != _vCoin.end();)
	{
		iter->img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdxX() - iter->x) * 64,
			CAMERA->getPos().y - (PLAYER->getPosIdxY() - iter->y) * 64);

		if (iter->x == PLAYER->getPosIdxX() && iter->y == PLAYER->getPosIdxY())
		{
			PLAYER->setCoin(PLAYER->getCoin() + iter->coinCount);
			SOUNDMANAGER->play("pickup_gold");
			iter = _vCoin.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void UIManager::addCoin(int idxX, int idxY, int coinCount)
{
	Coin coin;
	coin.img = IMAGEMANAGER->findImage("coin" + to_string(coinCount));
	coin.x = idxX;
	coin.y = idxY;
	coin.coinCount = coinCount;

	_vCoin.push_back(coin);
}
