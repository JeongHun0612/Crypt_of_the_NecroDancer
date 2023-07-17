#include "Stdafx.h"
#include "Armor.h"

HRESULT Armor::init()
{
	_type = ARMOR_TYPE::CLOTHES;
	_defense = 0;

	return S_OK;
}

void Armor::release()
{
}

void Armor::update()
{
}
