#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxX, int idxY)
{
	_img.frameCount = 0.0f;
	_img.frameX = 0;

	_effectImg.img = IMAGEMANAGER->findImage("enemy_effect");
	_effectImg.frameCount = 0.0f;
	_effectImg.frameX = 0;
	_effectImg.frameY = 0;
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();

	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");
	_heartImg = IMAGEMANAGER->findImage("small_heart");

	_vStage1Terrain = TILEMAP->getStage1Terrain();
	_vStage1Wall = TILEMAP->getStage1Wall();
	_maxTileCol = MAX_STAGE1_COL;

	_pos = { 0.f, 0.f };
	_posIdx = { idxX, idxY };
	_nextPosIdx = { idxX, idxY };

	_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
	_nextTileIdx = 0;
	_vStage1Terrain[_curTileIdx]->_isCollider = true;

	_distance = 0;

	_stepCount = 0;
	_beatCount = 0;
	_prevBeatCount = 0;

	_jumpPower = 5.0f;

	_isLeft = true;
	_isMove = false;
	_isAttack = false;

	return S_OK;
}

void Enemy::release()
{
	_vStage1Terrain[_curTileIdx]->_isCollider = false;

	UIMANAGER->addCoin(_posIdx.x, _posIdx.y, _coinCount);
}

void Enemy::update()
{
	// �÷��̾���� �Ÿ�
	_distance = sqrt(pow(_posIdx.x - PLAYER->getPosIdx().x, 2) + pow(_posIdx.y - PLAYER->getPosIdx().y, 2));

	// ������ Ÿ�̹�
	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount < _beatCount)
	{
		_stepCount++;
		_prevBeatCount = _beatCount;
	}

	// ������ �̹��� ����
	_img.frameCount += TIMEMANAGER->getDeltaTime();

	if (_img.frameCount >= 0.13f)
	{
		_img.img->setFrameX(_img.frameX);

		if (_img.frameX == _img.maxFrameX)
		{
			_img.frameX = 0;
		}
		
		if (_img.frameX < _img.maxFrameX)
		{
			_img.frameX++;
		}

		_img.frameCount = 0.f;
	}

	// ���� ��� ������ ����
	if (_isAttack)
	{
		_effectImg.frameCount += TIMEMANAGER->getDeltaTime();

		if (_effectImg.frameCount >= 0.13f)
		{
			_effectImg.img->setFrameX(_effectImg.frameX);

			if (_effectImg.frameX == _effectImg.maxFrameX)
			{
				_effectImg.frameX = 0;
				_isAttack = false;
			}
			else
			{
				_effectImg.frameX++;
			}
		}
	}
}

void Enemy::render(HDC hdc)
{
	// �Ÿ��� ���� ��� ��ȭ
	if (_distance > PLAYER->getLightPower())
	{
		_img.img->setFrameY(_img.frameY - 1);
	}
	else
	{
		_img.img->setFrameY(_img.frameY);
	}


	if (_distance < PLAYER->getLightPower() + 2)
	{
		// �׸��� ���
		_shadowImg->alphaRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8 + _pos.x,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 13 + _pos.y,
			180);

		// �̹��� ���
		_img.img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8 + _pos.x,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 18 +  _pos.y,
			_img.img->getFrameX(),
			_img.img->getFrameY());


		// HP ���
		if (_maxHP > _curHP && _curHP != 0)
		{
			for (int i = 0; i < _maxHP; i++)
			{
				if (i < _maxHP - _curHP)
				{
					_heartImg->setFrameX(1);
				}
				else
				{
					_heartImg->setFrameX(0);
				}

				_heartImg->frameRender(hdc,
					CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + (i * 25) + _pos.x,
					CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 43 + _pos.y,
					_heartImg->getFrameX(),
					_heartImg->getFrameY());
			}
		}

		// ���� ���
		if (_isAttack)
		{
			_effectImg.img->frameRender(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdx().x - _nextPosIdx.x) * 64 + 10,
				CAMERA->getPos().y - (PLAYER->getPosIdx().y - _nextPosIdx.y) * 64 - 8,
				_effectImg.img->getFrameX(),
				_effectImg.img->getFrameY());
		}
	}
}