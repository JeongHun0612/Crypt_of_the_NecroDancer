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
	RECT _rc;

	PLAYER_DIRECTION _curDirection;

	bool _isMove;
	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void moveAction(PLAYER_DIRECTION direction);

	Player() {}
	~Player() {}
};

