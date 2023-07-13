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

	POINTFLOAT	_pos;						// 현재 플레이어 포지션
	POINT		_posIdx;					// 현재 플레이어가 있는 타일번호

	RECT _rc;								// 플레이어 충돌체

	PLAYER_DIRECTION _curDirection;			// 플레이어 방향 정보

	bool _isMove;
	bool _isCollider;
	bool _isLeft;
	float _count;

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

	void setCollider(bool isCollider) { _isCollider = isCollider; }

	Player() {}
	~Player() {}
};

