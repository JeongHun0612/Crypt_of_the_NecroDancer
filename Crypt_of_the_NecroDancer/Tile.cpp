#include "Stdafx.h"
#include "Tile.h"

HRESULT Tile::init(int idxX, int idxY, int frameX, int frameY, bool isCollider, bool isExist, int hardNess, TERRAIN terrain)
{
	_idxX = idxX;
	_idxY = idxY;
	_frameX = frameX;
	_frameY = frameY;
	_isCollider = isCollider;
	_isExist = isExist;
	_hardNess = hardNess;
	_terrain = terrain;

	_isLight = false;

	return S_OK;
}

HRESULT Tile::init(int idxX, int idxY, int frameX, int frameY, bool isCollider, bool isExist, int hardNess, WALL wall)
{
	_idxX = idxX;
	_idxY = idxY;
	_frameX = frameX;
	_frameY = frameY;
	_isCollider = isCollider;
	_isExist = isExist;
	_hardNess = hardNess;
	_wall = wall;

	_isLight = false;

	return S_OK;
}
