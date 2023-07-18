#include "Stdafx.h"
#include "Shovel.h"

HRESULT Shovel::init()
{
	_img = IMAGEMANAGER->findImage("shovel");
	_hardNess = 1;

	return S_OK;
}

void Shovel::release()
{
}

void Shovel::update()
{
}

void Shovel::render(HDC hdc)
{
	for (auto iter = _vShowShovel.begin(); iter != _vShowShovel.end();)
	{
		iter->_img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdxX() - iter->_idxX) * 64 + 5,
			CAMERA->getPos().y - (PLAYER->getPosIdxY() - iter->_idxY) * 64 + 5);

		iter->_destoryTime += TIMEMANAGER->getDeltaTime();

		if (iter->_destoryTime >= 0.2f)
		{
			iter = _vShowShovel.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Shovel::addShowShovel(int idxX, int idxY)
{
	Shovel shovel;
	shovel._img = IMAGEMANAGER->findImage("shovel");
	shovel._idxX = idxX;
	shovel._idxY = idxY;
	shovel._destoryTime = 0.f;
	shovel._hardNess = 1;

	_vShowShovel.push_back(shovel);
}
