#include "../../../../../2DFrameWork/PCH/Stdafx.h"
#include "Wraith.h"

HRESULT Wraith::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	_type = ENEMY_TYPE::WRAITH;

    return S_OK;
}

void Wraith::release()
{
}

void Wraith::update()
{
}

void Wraith::render(HDC hdc)
{
}
