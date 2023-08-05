#include "../../../../2DFrameWork/PCH/Stdafx.h"
#include "Armor.h"

HRESULT Armor::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price, int tileMaxCol)
{
	Item::init(idxX, idxY, itemType, type, price, tileMaxCol);

	_slotImg = IMAGEMANAGER->findImage("slot_body");
	_img.img = IMAGEMANAGER->findImage("armor");
	_img.frameX = type - 1;
	_img.frameY = 0;

	switch ((ARMOR_TYPE)type)
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

	if (_isCollider && !_isChange)
	{
		// 플레이어의 소지금이 아이템의 가격보다 높을 때 
		if (PLAYER->getCoin() >= _price)
		{
			if (_price == 0)
			{
				SOUNDMANAGER->play("pickup_armor");
			}
			else
			{
				SOUNDMANAGER->play("pickup_purchase");
			}

			PLAYER->setCoin(PLAYER->getCoin() - _price);
			Armor* tempArmor = new Armor;
			tempArmor->init(_posIdx.x, _posIdx.y, _itemType, _type, 0, _tileMaxCol);

			if (PLAYER->getCurArmor() == nullptr)
			{
				UIMANAGER->getEquipment().push_back(this);

				_isSale = true;
			}
			else
			{
				_type = PLAYER->getCurArmor()->getType();
				_img.frameX = _type - 1;
				_defense = PLAYER->getCurArmor()->getDefense();
				_price = 0;
			}

			PLAYER->setCurArmor(tempArmor);
			_isChange = true;
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
