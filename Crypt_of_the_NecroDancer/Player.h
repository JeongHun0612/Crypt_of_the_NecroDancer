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
	GImage* _headImg;
	GImage* _bodyImg;

	POINTFLOAT	_pos;						// ���� �÷��̾� ������
	POINT		_posIdx;					// ���� �÷��̾ �ִ� Ÿ�Ϲ�ȣ

	RECT _rc;								// �÷��̾� �浹ü

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����

	bool _isMove;
	bool _isLeft;
	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	POINTFLOAT	getPos() { return _pos; }
	POINT		getPosIdx() { return _posIdx; }

	Player() {}
	~Player() {}
};

