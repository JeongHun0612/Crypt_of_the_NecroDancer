#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init(void)
{
	_prevHP = 0;

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
	for (auto iter = _vEquipment.begin(); iter != _vEquipment.end(); ++iter)
	{
		switch ((*iter)->getItemType())
		{
		case ITEM_TYPE::SHOVEL:
			break;
		case ITEM_TYPE::WEAPON:
			if (PLAYER->getCurWeapon()->getType() != (*iter)->getType())
			{
				(*iter) = PLAYER->getCurWeapon();
			}
			break;
		case ITEM_TYPE::ARMOR:
			if (PLAYER->getCurArmor()->getType() != (*iter)->getType())
			{
				(*iter) = PLAYER->getCurArmor();
			}
			break;
		}
	}

	for (auto iter = _vExpendable.begin(); iter != _vExpendable.end(); ++iter)
	{
		switch ((*iter)->getItemType())
		{
		case ITEM_TYPE::POTION:
			if (PLAYER->getCurPotion()->getType() != (*iter)->getType())
			{
				(*iter) = PLAYER->getCurPotion();
			}
			break;
		}
	}
}

void UIManager::render(HDC hdc)
{
	// 인벤토리 출력
	for (int i = 0; i < _vEquipment.size(); i++)
	{
		_vEquipment[i]->slotRender(hdc, { 10.0f + (i * 70.0f), 10.0f });
	}

	for (int i = 0; i < _vExpendable.size(); i++)
	{
		_vExpendable[i]->slotRender(hdc, { 10.0f, 80.0f + (i * 70.0f) });
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


	// 몬스터 소지금(동전)
	for (auto iter = _vCoin.begin(); iter != _vCoin.end();)
	{
		iter->img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - iter->x) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - iter->y) * 64 - 5);

		if (iter->x == PLAYER->getPosIdx().x && iter->y == PLAYER->getPosIdx().y)
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

	if (coinCount <= 10)
	{
		if (coinCount == 0) return;

		coin.img = IMAGEMANAGER->findImage("coin" + to_string(coinCount));
	}
	else
	{
		if (coinCount > 10 && coinCount <= 25)
		{
			coin.img = IMAGEMANAGER->findImage("coin_hoard_small");
		}
		else if (coinCount > 25 && coinCount <= 40)
		{
			coin.img = IMAGEMANAGER->findImage("coin_hoard_middle");
		}
		else
		{
			coin.img = IMAGEMANAGER->findImage("coin_hoard");
		}
	}

	coin.x = idxX;
	coin.y = idxY;
	coin.coinCount = coinCount;

	_vCoin.push_back(coin);
}

void UIManager::addEquipment(Item* equipment)
{
	_vEquipment.push_back(equipment);
}

void UIManager::deleteEquiment(Item* equipment)
{
	for (int i = 0; i < _vEquipment.size(); i++)
	{
		if (_vEquipment[i]->getItemType() == equipment->getItemType())
		{
			_vEquipment.erase(_vEquipment.begin() + i);
		}
	}
}

void UIManager::addExpendable(Item* expendable)
{
	_vExpendable.push_back(expendable);
}

void UIManager::deleteExpendable(Item* expendable)
{
	for (int i = 0; i < _vExpendable.size(); i++)
	{
		if (_vExpendable[i]->getItemType() == expendable->getItemType())
		{
			_vExpendable.erase(_vExpendable.begin() + i);
		}
	}
}

