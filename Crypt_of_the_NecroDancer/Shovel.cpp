#include "Stdafx.h"
#include "Shovel.h"

HRESULT Shovel::init()
{
	_img = IMAGEMANAGER->findImage("shovel");
	_hardNess = 1;
	_isDig = false;

	return S_OK;
}

void Shovel::release()
{
}

void Shovel::update()
{
}
