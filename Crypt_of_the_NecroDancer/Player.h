#pragma once
#include "SingletonBase.h"
#include "Shovel.h"
#include "Weapon.h"
#include "Armor.h"

enum class PLAYER_DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

class Player : public SingletonBase<Player>
{
private:

	GImage* _headImg;						// �÷��̾� �Ӹ� �̹���
	GImage* _bodyImg;						// �÷��̾� ���� �̹���
	GImage* _shadowImg;						// �÷��̾� �׸��� �̹���

	RECT _rc;								// �÷��̾� �浹ü

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����
	PLAYER_DIRECTION _nextDirection;		// �÷��̾� ���� ���� ����

	Shovel* _curShovel;						// �÷��̾ ���� ���� ��
	Weapon* _curWeapon;						// �÷��̾ ���� ���� ����
	Armor _curArmor;						// �÷��̾ ���� ���� ����

	POINTFLOAT _pos;						// ���� �÷��̾� ������
	int _posIdxX;							// ���� �÷��̾ �ִ� Ÿ���ε��� X
	int _posIdxY;							// ���� �÷��̾ �ִ� Ÿ���ε��� Y

	int _nextIdxX;							// �÷��̾��� ���� �ൿ ��ǥ X
	int _nextIdxY;							// �÷��̾��� ���� �ൿ ��ǥ Y

	float _jumpPower;						// ���� ����

	int _maxHP;								// �÷��̾� �ִ� ü��
	int _curHP;								// �÷��̾� ���� ü��
	int _lightPower;						// �Һ��� ����
	int _effectAlpha;						// �ǰ� ����Ʈ ���İ�
	int _shadowAlpha;						// �׸��� ���İ�

	int _coin;								// �÷��̾� ���� ����
	int _diamond;							// �÷��̾� ���� ���̾Ƹ��

	bool _isMove;							// �����̰� �ִ� ��������
	bool _isLeft;							// ������ �ٶ󺸰� �ִ� ��������
	bool _isHit;							// �÷��̾ �ǰ� ��������

	float _count;

public:
	HRESULT init(int startIdxX, int startIxY);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	// �÷��̾� ������
	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	int getPosIdxX() { return _posIdxX; }
	void setPosIdxX(int idxX) { _posIdxX = idxX; }

	int getPosIdxY() { return _posIdxY; }
	void setPosIdxY(int idxY) { _posIdxY = idxY; }

	int getNextIdxX() { return _nextIdxX; }
	void setNextIdxX(int idxX) { _nextIdxX = idxX; }

	int getNextIdxY() { return _nextIdxY; }
	void setNextIdxY(int idxY) { _nextIdxY = idxY; }


	// �÷��̾� ��ȭ
	void setCoin(int coin) { _coin = coin; }
	int getCoin() { return _coin; }
	int getDiamond() { return _diamond; }


	// �÷��̾� ü��
	void setMaxHP(int maxHP) { _maxHP = maxHP; }
	int getMaxHP() { return _maxHP; }

	void setCurHP(int curHP) { _curHP = curHP; }
	int getCurHP() { return _curHP; }


	// �÷��̾� �׸��� ���İ�
	void setShadowAlpha(int alpha) { _shadowAlpha = alpha; }


	// �÷��̾� �þ� ����
	void setLightPower(int lightPower) { _lightPower = lightPower; }
	int getLightPower() { return _lightPower; }


	// �÷��̾� �����¿� ����
	PLAYER_DIRECTION getCurDirection() { return _curDirection; }
	void setCurDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	PLAYER_DIRECTION getNextDirection() { return _nextDirection; }
	void setNextDirection(PLAYER_DIRECTION direction) { _nextDirection = direction; }


	// �÷��̾� ���� ����
	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }
	void setIsHit(bool isHit) { _isHit = isHit; }


	// �÷��̾� ���� ���
	Shovel* getCurShovel() { return _curShovel; }
	Weapon* getCurWeapon() { return _curWeapon; }

	Player() {}
	~Player() {}
};

