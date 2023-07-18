#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxX, int idxY, int heart)
{
	_img = IMAGEMANAGER->findImage("slime_blue");
	_idxX = idxX;
	_idxY = idxY;
	_heart = heart;

	_img->setFrameY(1);

    return S_OK;
}

void Slime_Blue::release()
{
}

void Slime_Blue::update()
{
	Slime::update();


}

void Slime_Blue::render(HDC hdc)
{
	Slime::render(hdc);
}
