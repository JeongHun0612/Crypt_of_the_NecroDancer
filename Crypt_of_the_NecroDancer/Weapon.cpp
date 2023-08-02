#include "Stdafx.h"
#include "Weapon.h"

HRESULT Weapon::init()
{
	_slotImg = IMAGEMANAGER->findImage("slot_weapon");
	_img.img = IMAGEMANAGER->findImage("dagger");
	_effectImg.img = IMAGEMANAGER->findImage("effect_dagger");
	_power = 1;

	return S_OK;
}


void Weapon::release()
{
}

void Weapon::update()
{
	//_count++;

	//if (_count % 5 == 0)
	//{
	//	if (_effectImg->getFrameX() == _effectImg->getMaxFrameX())
	//	{
	//		_effectImg->setFrameX(0);
	//		PLAYER->setIsAttack(false);
	//	}

	//	_effectImg->setFrameX(_effectImg->getFrameX() + 1);
	//}
}

void Weapon::render(HDC hdc)
{
	//// 이미지 출력
	//_img.img->frameRender(hdc,
	//	(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2 + _pos.x,
	//	(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight() + _pos.y,
	//	_img.frameX,
	//	_img.img->getFrameY());

}

void Weapon::effectRender(HDC hdc)
{
	// 이펙트 출력
	switch (PLAYER->getCurDirection())
	{
	case PLAYER_DIRECTION::LEFT:
		_effectImg.img->frameRender(hdc, CAMERA->getPos().x - 64, CAMERA->getPos().y - 20, _effectImg.img->getFrameX(), 2);
		break;
	case PLAYER_DIRECTION::RIGHT:
		_effectImg.img->frameRender(hdc, CAMERA->getPos().x + 64, CAMERA->getPos().y - 20, _effectImg.img->getFrameX(), 3);
		break;
	case PLAYER_DIRECTION::UP:
		_effectImg.img->frameRender(hdc, CAMERA->getPos().x, CAMERA->getPos().y - 64, _effectImg.img->getFrameX(), 0);
		break;
	case PLAYER_DIRECTION::DOWN:
		_effectImg.img->frameRender(hdc, CAMERA->getPos().x, CAMERA->getPos().y + 64, _effectImg.img->getFrameX(), 1);
		break;
	}
}
