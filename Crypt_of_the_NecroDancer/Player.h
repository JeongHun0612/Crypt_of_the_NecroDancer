#pragma once
#include "GameNode.h"

enum class PLAYER_DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Player : public GameNode
{
private:
	GImage* _headImg;						// �÷��̾� �Ӹ� �̹���
	GImage* _bodyImg;						// �÷��̾� ���� �̹���

	POINTFLOAT _pos;						// ���� �÷��̾� ������
	POINT _posIdx;							// ���� �÷��̾ �ִ� Ÿ�Ϲ�ȣ

	RECT _rc;								// �÷��̾� �浹ü

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����

	bool _isMove;
	bool _isLeft;
	float _count;

	GImage* _shovelItemImg;
	GImage* _weaponItemImg;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	POINT		getPosIdx() { return _posIdx; }
	void setPosIdx(int x, int y) { _posIdx.x = x, _posIdx.y = y; }

	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }

	void setDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	Player() {}
	~Player() {}
};

