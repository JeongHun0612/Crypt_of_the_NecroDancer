#include "Stdafx.h"
#include "Armor.h"

HRESULT Armor::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price)
{
	Item::init(idxX, idxY, itemType, type, price);

	_slotImg = IMAGEMANAGER->findImage("slot_body");
	_img.img = IMAGEMANAGER->findImage("armor");
	_img.frameX = type - 1;
	_img.frameY = 0;

	_armorType = (ARMOR_TYPE)type;

	switch (_armorType)
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
	Item::release();
}

void Armor::update()
{
	Item::update();

	if (_posIdx.x == PLAYER->getPosIdx().x && _posIdx.y == PLAYER->getPosIdx().y)
	{
		// 플레이어의 소지금이 아이템의 가격보다 높을 때 
		if (PLAYER->getCoin() >= _price)
		{
			if (PLAYER->getCurArmor() == nullptr)
			{
				UIMANAGER->addEquipment(this);
			}

			PLAYER->setCoin(PLAYER->getCoin() - _price);
			PLAYER->setCurArmor(this);
			_isSale = true;
		}
	}
}

void Armor::render(HDC hdc)
{
	Item::render(hdc);
}

void Armor::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);
}
