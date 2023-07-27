#include "Stdafx.h"
#include "ShopKeeper.h"

HRESULT ShopKeeper::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_type = ENEMY_TYPE::SHOPKEEPER;

	_img.img = IMAGEMANAGER->findImage("shopkeeper");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_maxHP = 9;
	_curHP = _maxHP;

	_power = 10;

	_coinCount = 0;

	_isInvincible = true;

	return S_OK;
}

void ShopKeeper::release()
{
	Enemy::release();
}

void ShopKeeper::update()
{
	Enemy::update();

	if (_distance < 15)
	{
		SOUNDMANAGER->setVolume("stage1_1_shopkeeper", 1.0f - (_distance * 0.06f));
	}
	else
	{
		SOUNDMANAGER->setVolume("stage1_1_shopkeeper", 0.0f);
	}
}

void ShopKeeper::render(HDC hdc)
{
	Enemy::render(hdc);
}
