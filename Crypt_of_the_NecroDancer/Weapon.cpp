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

}
