#pragma once
#include "SingletonBase.h"

enum class PLAYER_DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class Player : public SingletonBase<Player>
{
private:
	struct Shovel
	{
		GImage* img;
		int hardness;
	};


private:
	GImage* _headImg;						// �÷��̾� �Ӹ� �̹���
	GImage* _bodyImg;						// �÷��̾� ���� �̹���

	GImage* _weaponItemImg;

	POINTFLOAT _pos;						// ���� �÷��̾� ������
	POINT _posIdx;							// ���� �÷��̾ �ִ� Ÿ�Ϲ�ȣ

	RECT _rc;								// �÷��̾� �浹ü

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����

	Shovel _curShovel;						// �÷��̾� ���� �������� ��

	int _maxHP;								// �÷��̾� �ִ� ü��
	int _curHP;								// �÷��̾� ���� ü��

	int _coin;								// �÷��̾� ���� ����
	int _diamond;							// �÷��̾� ���� ���̾Ƹ��

	bool _isMove;
	bool _isLeft;

	bool _isShovel;

	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	POINT getPosIdx() { return _posIdx; }
	void setPosIdx(int x, int y) { _posIdx.x = x, _posIdx.y = y; }

	int getCoin() { return _coin; }
	int getDiamond() { return _diamond; }

	void setMaxHP(int maxHP) { _maxHP = maxHP; }
	int getMaxHP() { return _maxHP; }

	void setCurHP(int curHP) { _curHP = curHP; }
	int getCurHP() { return _curHP; }

	void setDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }

	void setIsShovel(bool isShovel) { _isShovel = isShovel; }
	bool getIsShovel() { return _isShovel; }


	Shovel getShovel() { return _curShovel; }

	Player() {}
	~Player() {}
};

