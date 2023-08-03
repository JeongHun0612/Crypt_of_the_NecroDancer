#include "Stdafx.h"
#include "Potion.h"

HRESULT Potion::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price)
{
	Item::init(idxX, idxY, itemType, type, price);

	_slotImg = IMAGEMANAGER->findImage("slot_item");
	_img.img = IMAGEMANAGER->findImage("potion");
	_img.frameX = type;
	_img.frameY = 0;

	switch (_type)
	{
	case 0:
		_recoveryAmount = 2;
		break;
	case 1:
		_recoveryAmount = 4;
		break;
	case 2:
		_recoveryAmount = 6;
		break;
	}

	return S_OK;
}

void Potion::release()
{
	Item::release();
}

void Potion::update()
{
	Item::update();

	if (_isCollider && !_isChange)
	{
		// 플레이어의 소지금이 아이템의 가격보다 높을 때 
		if (PLAYER->getCoin() >= _price)
		{
			if (_price == 0)
			{
				//SOUNDMANAGER->play("pickup_armor");
			}
			else
			{
				SOUNDMANAGER->play("pickup_purchase");
			}

			PLAYER->setCoin(PLAYER->getCoin() - _price);
			Potion* tempPotion = new Potion;
			tempPotion->init(_posIdx.x, _posIdx.y, _itemType, _type, 0);

			if (PLAYER->getCurPotion() == nullptr)
			{
				UIMANAGER->addExpendable(this);
				_isSale = true;
			}
			else
			{
				_type = PLAYER->getCurPotion()->getType();
				_img.frameX = _type;
				_recoveryAmount = PLAYER->getCurPotion()->getRecoveryAmount();
				_price = 0;
			}

			PLAYER->setCurPotion(tempPotion);
			_isChange = true;
		}
	}
}

void Potion::render(HDC hdc)
{
	Item::render(hdc);
}

void Potion::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);
}
