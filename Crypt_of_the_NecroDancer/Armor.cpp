#include "Stdafx.h"
#include "Armor.h"

HRESULT Armor::init(int idxX, int idxY, int type)
{
	_type = (ARMOR_TYPE)type;

	_img.img = IMAGEMANAGER->findImage("armor");
	_img.frameX = type;
	_img.frameY = 0;

	_posIdx = { idxX, idxY };

	switch (_type)
	{
	case ARMOR_TYPE::CLOTHES:
		_defense = 0;
		break;
	case ARMOR_TYPE::LEATHER:
		_defense = 1;
		break;
	case ARMOR_TYPE::CHAINMAIL:
		_defense = 2;
		break;
	case ARMOR_TYPE::PLATE:
		_defense = 3;
		break;
	case ARMOR_TYPE::HEAVY:
		_defense = 4;
		break;
	}

	return S_OK;
}

void Armor::release()
{
}

void Armor::update()
{
}

void Armor::render(HDC hdc)
{
}
