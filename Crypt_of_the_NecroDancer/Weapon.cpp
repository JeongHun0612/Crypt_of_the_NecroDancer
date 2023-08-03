#include "Stdafx.h"
#include "Weapon.h"

HRESULT Weapon::init()
{
	Item::init();

	_slotImg = IMAGEMANAGER->findImage("slot_attack");
	_img.img = IMAGEMANAGER->findImage("weapon");
	_img.frameX = 0;
	_img.frameY = 0;

	_effectImg.img = IMAGEMANAGER->findImage("effect_dagger");
	_effectImg.frameX = 0;
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();

	_itemType = ITEM_TYPE::WEAPON;
	_weaponType = WEAPON_TYPE::DAGGER;

	_power = 1;

	return S_OK;
}

HRESULT Weapon::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price)
{
	Item::init(idxX, idxY, itemType, type, price);

	_slotImg = IMAGEMANAGER->findImage("slot_attack");
	_img.img = IMAGEMANAGER->findImage("weapon");
	_img.frameX = type;
	_img.frameY = 0;

	_weaponType = (WEAPON_TYPE)type;

	switch (_weaponType)
	{
	case WEAPON_TYPE::DAGGER:
		_power = 1;
		break;
	case WEAPON_TYPE::BROADSWORD:
		_power = 2;
		break;
	case WEAPON_TYPE::BOW:
		_power = 2;
		break;
	}

	return S_OK;
}


void Weapon::release()
{
	Item::release();
}

void Weapon::update()
{
	Item::update();

	if (_posIdx.x == PLAYER->getPosIdx().x && _posIdx.y == PLAYER->getPosIdx().y)
	{
		// �÷��̾��� �������� �������� ���ݺ��� ���� �� 
		if (PLAYER->getCoin() >= _price)
		{
			PLAYER->setCoin(PLAYER->getCoin() - _price);
			PLAYER->setCurWeapon(this);
			_isSale = true;
		}
	}
}

void Weapon::render(HDC hdc)
{
	Item::render(hdc);
}

void Weapon::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);
}

void Weapon::effectRender(HDC hdc)
{
	// ���� ����Ʈ ������ ����
	_effectImg.frameCount += TIMEMANAGER->getDeltaTime();

	if (_effectImg.frameCount >= 0.06f)
	{
		if (_effectImg.frameX == _effectImg.maxFrameX)
		{
			_effectImg.frameX = 0;
			PLAYER->setIsAttack(false);
		}
		else
		{
			_effectImg.frameX++;
		}

		_effectImg.frameCount = 0.0f;
	}

	// ����Ʈ ���
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
