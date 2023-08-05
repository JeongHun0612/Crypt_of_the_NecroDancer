#include "../../../../../2DFrameWork/PCH/Stdafx.h"
#include "Skeleton_Normal.h"

HRESULT Skeleton_Normal::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	Skeleton::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::SKELETON_NORMAL;

	_img.img = IMAGEMANAGER->findImage("skeleton_normal");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 5;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 1;

	_coinCount = RND->getFromIntTo(4, 6);

	return S_OK;
}

void Skeleton_Normal::release()
{
	Skeleton::release();
}

void Skeleton_Normal::update()
{
	Skeleton::update();
}

void Skeleton_Normal::render(HDC hdc)
{
	Skeleton::render(hdc);
}