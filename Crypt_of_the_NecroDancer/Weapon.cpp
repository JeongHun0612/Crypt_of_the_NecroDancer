#include "Stdafx.h"
#include "Weapon.h"

HRESULT Weapon::init(WEAPON_TYPE type)
{
	switch (type)
	{
	case WEAPON_TYPE::DAGGER:
		_img = IMAGEMANAGER->findImage("dagger");
		_effect = IMAGEMANAGER->findImage("effect_dagger");
		_type = WEAPON_TYPE::DAGGER;
		_power = 1;
		break;
	case WEAPON_TYPE::BROADSWORD:
		_img = IMAGEMANAGER->findImage("sword");
		_effect = IMAGEMANAGER->findImage("effect_dagger");
		_type = WEAPON_TYPE::BROADSWORD;
		_power = 2;
		break;
	case WEAPON_TYPE::RAPIER:
		break;
	case WEAPON_TYPE::SPEAR:
		break;
	case WEAPON_TYPE::END:
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

void Weapon::attack()
{
}

void Weapon::changeWeapon(Weapon &weapon, WEAPON_TYPE type)
{
	switch (type)
	{
	case WEAPON_TYPE::DAGGER:
		weapon._img = IMAGEMANAGER->findImage("dagger");
		weapon._effect = IMAGEMANAGER->findImage("effect_dagger");
		weapon._type = WEAPON_TYPE::DAGGER;
		weapon._power = 1;
		break;
	case WEAPON_TYPE::BROADSWORD:
		weapon._img = IMAGEMANAGER->findImage("sword");
		weapon._effect = IMAGEMANAGER->findImage("effect_dagger");
		weapon._type = WEAPON_TYPE::BROADSWORD;
		weapon._power = 2;
		break;
	case WEAPON_TYPE::RAPIER:
		break;
	case WEAPON_TYPE::SPEAR:
		break;
	case WEAPON_TYPE::END:
		break;
	}
}
