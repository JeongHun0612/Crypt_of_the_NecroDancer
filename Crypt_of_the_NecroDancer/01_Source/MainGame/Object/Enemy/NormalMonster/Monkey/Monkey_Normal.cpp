#include "../../../../../2DFrameWork/PCH/Stdafx.h"
#include "Monkey_Normal.h"

HRESULT Monkey_Normal::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	Monkey::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::MONKEY_NORMAL;

	_img.img = IMAGEMANAGER->findImage("monkey_normal");
	_img.maxFrameX = 3;
	_img.frameY = 1;

	_maxHP = 1;
	_grabMaxHP = 4;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = RND->getFromIntTo(2, 4);

	_curMoveDirection = 0;

	return S_OK;
}

void Monkey_Normal::release()
{
	Monkey::release();
}

void Monkey_Normal::update()
{
	Monkey::update();

	if (_isHit)
	{
		SOUNDMANAGER->play("monkey_hit");
		_isHit = false;
	}
}

void Monkey_Normal::render(HDC hdc)
{
	Monkey::render(hdc);
}
