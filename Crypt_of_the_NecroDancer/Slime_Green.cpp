#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(int idxX, int idxY, int heart)
{
	_img = IMAGEMANAGER->findImage("slime_green");
	_idxX = idxX;
	_idxY = idxY;
	_heart = heart;

	_img->setFrameY(1);

	return S_OK;
}

void Slime_Green::release()
{
}

void Slime_Green::update()
{
	Slime::update();

	//_count += TIMEMANAGER->getDeltaTime();

	//if (_count >= 0.25f)
	//{
	//	if (_img->getFrameX() == _img->getMaxFrameX())
	//	{
	//		_img->setFrameX(0);
	//	}

	//	_img->setFrameX(_img->getFrameX() + 1);

	//	_count = 0.f;
	//}
}

void Slime_Green::render(HDC hdc)
{
	Slime::render(hdc);
	//int distance = sqrt(pow(_idxX - PLAYER->getPosIdxX(), 2) + pow(_idxY - PLAYER->getPosIdxY(), 2));

	//if (distance > PLAYER->getLightDist())
	//{
	//	_img->setFrameY(0);
	//}
	//else
	//{
	//	_img->setFrameY(1);
	//}

	//_img->frameRender(hdc,
	//	CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64,
	//	CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64,
	//	_img->getFrameX(), _img->getFrameY());
}
