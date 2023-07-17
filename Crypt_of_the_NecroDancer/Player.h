#pragma once
#include "SingletonBase.h"
#include "Shovel.h"
#include "Weapon.h"
#include "Armor.h"

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
	GImage* _headImg;						// �÷��̾� �Ӹ� �̹���
	GImage* _bodyImg;						// �÷��̾� ���� �̹���

	Shovel* _curShovel;						// �÷��̾ ���� ���� ��
	Weapon _curWeapon;						// �÷��̾ ���� ���� ����
	Armor _curArmor;						// �÷��̾ ���� ���� ����

	POINTFLOAT _pos;						// ���� �÷��̾� ������
	int _posIdxX;							// ���� �÷��̾ �ִ� Ÿ���ε��� X
	int _posIdxY;							// ���� �÷��̾ �ִ� Ÿ���ε��� Y

	RECT _rc;								// �÷��̾� �浹ü

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����

	int _maxHP;								// �÷��̾� �ִ� ü��
	int _curHP;								// �÷��̾� ���� ü��
	int _rightDist;							// �Һ��� �Ÿ�

	int _coin;								// �÷��̾� ���� ����
	int _diamond;							// �÷��̾� ���� ���̾Ƹ��

	bool _isMove;							// �����̰� �ִ� ��������
	bool _isLeft;							// ������ �ٶ󺸰� �ִ� ��������

	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);
	void showShovel(PLAYER_DIRECTION direction, HDC hdc);


	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	int getPosIdxX() { return _posIdxX; }
	void setPosIdxX(int idxX) { _posIdxX = idxX; }

	int getPosIdxY() { return _posIdxY; }
	void setPosIdxY(int idxY) { _posIdxY = idxY; }

	int getCoin() { return _coin; }
	int getDiamond() { return _diamond; }

	void setMaxHP(int maxHP) { _maxHP = maxHP; }
	int getMaxHP() { return _maxHP; }

	void setCurHP(int curHP) { _curHP = curHP; }
	int getCurHP() { return _curHP; }

	void setRightDist(int rightDist) { _rightDist = rightDist; }
	int getRightDist() { return _rightDist; }

	PLAYER_DIRECTION getCurDirection() { return _curDirection; }
	void setCurDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }

	Shovel* getCurShovel() { return _curShovel; }

	Player() {}
	~Player() {}
};

