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

	POINT _pos;
	POINT _posIdx;

	RECT _rc;

	PLAYER_DIRECTION _curDirection;

	bool _isMove;
	bool _isLeft;
	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	POINT getPos() { return _pos; }
	POINT getPosIdx() { return _posIdx; }

	Player() {}
	~Player() {}
};

