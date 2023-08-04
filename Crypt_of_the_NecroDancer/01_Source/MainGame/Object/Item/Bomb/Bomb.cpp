#include "Stdafx.h"
#include "Bomb.h"

HRESULT Bomb::init()
{
	_slotImg = IMAGEMANAGER->findImage("slot_bomb");
	_img.img = IMAGEMANAGER->findImage("bomb");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.startFrameX = 0;
	_img.frameX = 0;
	_img.frameY = 0;

	_effectImg.img = IMAGEMANAGER->findImage("effect_explosion");
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();
	_effectImg.frameX = 0;
	_effectImg.frameY = 0;

	_itemType = ITEM_TYPE::BOMB;
	_type = 0;

	_power = 4;
	_beatCount = 0;
	_prevBeatCount = -1;
	_stepCount = 0;

	_isExplosion = false;

	return S_OK;
}

HRESULT Bomb::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price, int tileMaxCol)
{
	Item::init(idxX, idxY, itemType, type, price, tileMaxCol);

	_slotImg = IMAGEMANAGER->findImage("slot_bomb");
	_img.img = IMAGEMANAGER->findImage("bomb");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameX = 0;
	_img.frameY = 0;

	_effectImg.img = IMAGEMANAGER->findImage("effect_explosion");
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();
	_effectImg.frameX = 0;
	_effectImg.frameY = 0;

	_itemType = ITEM_TYPE::BOMB;
	_type = 0;

	_power = 4;

	_isExplosion = false;

	return S_OK;
}

void Bomb::release()
{
	Item::release();
}

void Bomb::update()
{
	Item::update();

	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount < _beatCount)
	{
		_stepCount++;
		_prevBeatCount = _beatCount;
	}

	switch (_stepCount)
	{
	case 1:
		_img.startFrameX = 0;
		_img.maxFrameX = 1;
		break;
	case 2:
		_img.startFrameX = 2;
		_img.maxFrameX = 3;
		break;
	case 3:
		_img.startFrameX = 4;
		_img.maxFrameX = 4;
		break;
	}

	if (_stepCount < 4)
	{
		_img.frameCount += TIMEMANAGER->getDeltaTime();

		if (_img.frameCount >= 0.3f)
		{
			if (_img.frameX == _img.maxFrameX)
			{
				_img.startFrameX = _img.maxFrameX;
			}
			else
			{
				_img.frameX++;
			}

			_img.frameCount = 0.0f;
		}
	}

	if (_stepCount == 4)
	{
		if (!_isExplosion)
		{
			// 폭발 범위 내 오브젝트 검사
			for (int i = 0; i < 8; i++)
			{
				Vec2 nextPosIdx;
				nextPosIdx.x = _posIdx.x + _explosionRange[i].x;
				nextPosIdx.y = _posIdx.y + _explosionRange[i].y;

				int nextTileIdx = (PLAYER->getTileMaxCol() * nextPosIdx.y) + nextPosIdx.x;

				// 플레이어 검사
				if (nextPosIdx.x == PLAYER->getPosIdx().x && nextPosIdx.y == PLAYER->getPosIdx().y && !PLAYER->getIsInvincible() && !PLAYER->getIsLobby())
				{
					PLAYER->setIsHit(true);
					PLAYER->setCurHP(PLAYER->getCurHP() - _power / 2);
				}

				// 벽 오브젝트 검사
				if (PLAYER->getWallTile()[nextTileIdx]->_isCollider && PLAYER->getWallTile()[nextTileIdx]->_hardNess <= _power)
				{
					PLAYER->getWallTile()[nextTileIdx]->_isCollider = false;
					PLAYER->getWallTile()[nextTileIdx]->_isExist = false;

					if (PLAYER->getWallTile()[nextTileIdx]->_wallType == WALL_TYPE::GOLDWALL)
					{
						UIMANAGER->addCoin(nextPosIdx.x, nextPosIdx.y, 10);
					}
				}

				// 적 객체 검사
				for (int i = 0; i < PLAYER->getEnemyList().size(); i++)
				{
					if (nextPosIdx.x == PLAYER->getEnemyList()[i]->getPosIdx().x && nextPosIdx.y == PLAYER->getEnemyList()[i]->getPosIdx().y)
					{
						PLAYER->getEnemyList()[i]->setCurHP(PLAYER->getEnemyList()[i]->getCurHP() - _power);
						break;
					}
				}
			}

			_isExplosion = true;
		}

		_effectImg.frameCount += TIMEMANAGER->getDeltaTime();

		if (_effectImg.frameCount >= 0.04f)
		{
			if (_effectImg.frameX == _effectImg.maxFrameX)
			{
				_stepCount = 0;
				PLAYER->setIsBomb(false);
				PLAYER->setCurBomb(nullptr);
			}
			else
			{
				_effectImg.frameX++;
			}

			_effectImg.frameCount = 0.0f;
		}
	}
}


void Bomb::render(HDC hdc)
{
	Item::render(hdc);
}

void Bomb::effectRender(HDC hdc)
{
	if (_stepCount < 4)
	{
		// 아이템 출력
		_img.img->frameRender(hdc,
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2,
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight(),
			_img.frameX,
			_img.img->getFrameY());
	}

	if (_stepCount == 4)
	{
		// 폭발 출력
		_effectImg.img->frameRender(hdc,
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _effectImg.img->getFrameWidth() / 2,
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _effectImg.img->getFrameHeight() / 2,
			_effectImg.frameX,
			_effectImg.img->getFrameY());
	}
}

void Bomb::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);

	_img.img->frameRender(hdc,
		pos.x + 30 - _img.img->getFrameWidth() / 2,
		pos.y + 38 - _img.img->getFrameHeight() / 2,
		_img.frameX,
		_img.frameY);
}
