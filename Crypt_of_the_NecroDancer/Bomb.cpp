#include "Stdafx.h"
#include "Bomb.h"

HRESULT Bomb::init()
{
	Item::init();

	_count = 2;

	_slotImg = IMAGEMANAGER->findImage("slot_bomb");
	_img.img = IMAGEMANAGER->findImage("bomb");
	_img.frameX = 0;
	_img.frameY = 0;

	_effectImg.img = IMAGEMANAGER->findImage("effect_explosion");
	_effectImg.frameX = 0;
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();

	_itemType = ITEM_TYPE::BOMB;
	_type = 0;

	_power = 4;

	_isExplosion = false;

	return S_OK;
}

HRESULT Bomb::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price)
{
	Item::init(idxX, idxY, itemType, type, price);

	_slotImg = IMAGEMANAGER->findImage("slot_bomb");
	_img.img = IMAGEMANAGER->findImage("bomb");
	_img.frameX = 0;
	_img.frameY = 0;

	_power = 4;

	_isExplosion = false;

	return S_OK;
}

void Bomb::release()
{
	Item::release();
}

void Bomb::update()
{
	Item::update();
}

void Bomb::render(HDC hdc)
{
	Item::render(hdc);
}

void Bomb::render(HDC hdc, int beatCount)
{
	_img.frameCount += TIMEMANAGER->getDeltaTime();

	if (_img.frameCount >= 0.06f)
	{
		if (_img.frameX == _img.maxFrameX)
		{
			_img.frameX = 0;
			//PLAYER->setIsAttack(false);
		}
		else
		{
			_img.frameX++;
		}

		_img.frameCount = 0.0f;
	}

	// 아이템 출력
	_img.img->frameRender(hdc,
		(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2,
		(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight(),
		_img.frameX,
		_img.img->getFrameY());
}

void Bomb::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);

	_img.img->frameRender(hdc,
		pos.x + 30 - _img.img->getFrameWidth() / 2,
		pos.y + 38 - _img.img->getFrameHeight() / 2,
		_img.frameX,
		_img.frameY);

	IMAGEMANAGER->findImage("x_button")->render(hdc,
		pos.x + 25,
		pos.y + 45);

	IMAGEMANAGER->findImage("small_number")->frameRender(hdc, pos.x + 40, pos.y + 45, _count, 0);
}
