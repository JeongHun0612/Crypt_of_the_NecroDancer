#include "Stdafx.h"
#include "Skeleton_Normal.h"

HRESULT Skeleton_Normal::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);
	_img = IMAGEMANAGER->findImage("skeleton_normal");

	_img->setFrameY(5);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 1;

	_coinCount = 5;

	return S_OK;
}

void Skeleton_Normal::release()
{
	Enemy::release();
}

void Skeleton_Normal::update()
{
	Enemy::update();

	if (_isMove)
	{
		// 4���� Ž�� �� ���� ����
		for (int i = 0; i < 4; i++)
		{
			distance[i] = abs(_idxX + direction[i].x - PLAYER->getPosIdxX()) + abs(_idxY + direction[i].y - PLAYER->getPosIdxY());

			if (_idxX + direction[i].x == PLAYER->getPosIdxX() && _idxY + direction[i].y == PLAYER->getPosIdxY())
			{
				_isAttack = true;
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);

				_nextIdxX = _idxX + direction[i].x;
				_nextIdxY = _idxY + direction[i].y;
			}
		}

		if (!_isAttack)
		{
			if (PLAYER->getPosIdxX() < _idxX)
			{
				_nextIdxX = _idxX - 1;

				for (int i = 0; i < ENEMYMANAGER->getEnemyList().size(); i++)
				{
					if (_nextIdxX == ENEMYMANAGER->getEnemyList()[i]->getIdxX() && _idxY == ENEMYMANAGER->getEnemyList()[i]->getIdxY())
					{
						//cout << "���� �浹" << endl;
						_nextIdxX = _idxX;
					}
				}

				for (auto iter = _vStage1Wall.begin(); iter != _vStage1Wall.end(); ++iter)
				{

				}

				if (PLAYER->getPosIdxY() < _idxY)
				{
					// ���� ��
					//_frameY = 1;
					//_nextIdxY = _idxY - 1;
				}
				else
				{
					// ���� �Ʒ�
					//_frameY = 5;
					//_nextIdxY = _idxY + 1;
				}
			}
			else
			{
				//if (PLAYER->getPosIdxY() < _idxY)
				//{
				//	// ������ ��
				//	_frameY = 3;
				//}
				//else
				//{
				//	// ������ �Ʒ�
				//	_frameY = 7;
				//}
			}
		}





		_isMove = false;
	}

	//if (abs(PLAYER->getPosIdxX() - _idxX) > abs(PLAYER->getPosIdxY() - _idxY))
	//{
	//	if (PLAYER->getPosIdxX() - _idxX > 0)
	//	{
	//		cout << "������" << endl;
	//	}
	//	else
	//	{
	//		cout << "����" << endl;
	//	}
	//}
	//else
	//{
	//	if (PLAYER->getPosIdxY() - _idxY > 0)
	//	{
	//		cout << "�Ʒ�" << endl;
	//	}
	//	else
	//	{
	//		cout << "��" << endl;
	//	}
	//}
}

void Skeleton_Normal::render(HDC hdc)
{
	Enemy::render(hdc);
}
