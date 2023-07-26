#include "Stdafx.h"
#include "Weapon.h"

HRESULT Weapon::init(WEAPON_TYPE type)
{
	switch (type)
	{
	case WEAPON_TYPE::DAGGER:
		_img = IMAGEMANAGER->findImage("dagger");
		_effectImg = IMAGEMANAGER->findImage("effect_dagger");
		_power = 1;
		break;
	case WEAPON_TYPE::BROADSWORD:
		_img = IMAGEMANAGER->findImage("sword");
		_effectImg = IMAGEMANAGER->findImage("effect_dagger");
		_power = 2;
		break;
	case WEAPON_TYPE::RAPIER:
		break;
	case WEAPON_TYPE::SPEAR:
		break;
	default:
		break;
	}

	return S_OK;
}

void Weapon::release()
{
}

void Weapon::update()
{
	_count++;

	if (_count % 5 == 0)
	{
		if (_effectImg->getFrameX() == _effectImg->getMaxFrameX())
		{
			_effectImg->setFrameX(0);
			PLAYER->setIsAttack(false);
		}

		_effectImg->setFrameX(_effectImg->getFrameX() + 1);
	}
}

void Weapon::render(HDC hdc)
{
	// ÀÌÆåÆ® Ãâ·Â
	switch (PLAYER->getCurDirection())
	{
	case PLAYER_DIRECTION::LEFT:
		_effectImg->frameRender(hdc, CAMERA->getPos().x - 64, CAMERA->getPos().y - 20, _effectImg->getFrameX(), 2);
		break;
	case PLAYER_DIRECTION::RIGHT:
		_effectImg->frameRender(hdc, CAMERA->getPos().x + 64, CAMERA->getPos().y - 20, _effectImg->getFrameX(), 3);
		break;
	case PLAYER_DIRECTION::UP:
		_effectImg->frameRender(hdc, CAMERA->getPos().x, CAMERA->getPos().y - 64, _effectImg->getFrameX(), 0);
		break;
	case PLAYER_DIRECTION::DOWN:
		_effectImg->frameRender(hdc, CAMERA->getPos().x, CAMERA->getPos().y + 64, _effectImg->getFrameX(), 1);
		break;
	}
}
