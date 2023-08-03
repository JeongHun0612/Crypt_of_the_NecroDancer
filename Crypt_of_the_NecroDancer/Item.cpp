#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init()
{

	return S_OK;
}

HRESULT Item::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price)
{
	_itemType = itemType;
	_posIdx = { idxX, idxY };
	_price = price;
	_isSale = false;

	return S_OK;
}

void Item::release()
{
	cout << "Item Delete" << endl;
}

void Item::update()
{
	// 플레이어와의 거리
	_distance = abs(_posIdx.x - PLAYER->getPosIdx().x) + abs(_posIdx.y - PLAYER->getPosIdx().y);
}

void Item::render(HDC hdc)
{
	if (_distance < 11)
	{
		if (_distance > PLAYER->getLightPower() - 1)
		{
			_img.img->setFrameY(_img.frameY + 1);
		}
		else
		{
			_img.img->setFrameY(_img.frameY);

			// 가격 출력
			if (_price != 0)
			{
				for (int i = 0; i < to_string(_price).size(); i++)
				{
					IMAGEMANAGER->findImage("number")->frameRender(hdc,
						(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 19 + (i * 15),
						(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 35,
						to_string(_price)[i] - 48,
						0);
				}
			}
		}

		// 아이템 출력
		_img.img->frameRender(hdc,
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2,
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight(),
			_img.frameX,
			_img.img->getFrameY());
	}
}

void Item::slotRender(HDC hdc, Vec2_F pos)
{
	_slotImg->render(hdc, pos.x, pos.y);

	_img.img->frameRender(hdc,
		pos.x + 30 - _img.img->getFrameWidth() / 2,
		pos.y + 38 - _img.img->getFrameHeight() / 2,
		_img.frameX,
		_img.frameY);
}
