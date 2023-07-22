#pragma once

enum ENEMY_DIRECTION
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

class Enemy
{
protected:
	// Left - Up - Right - Down
	Vec2 _fourDirection[4] =
	{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

	GImage* _img;
	GImage* _shadowImg;
	GImage* _heartImg;
	GImage* _effectImg;

	vector<Tile*> _vStage1Wall;

	int _attackDirection;
	int _distance;

	Vec2_F _pos;
	Vec2 _posIdx;
	Vec2 _nextPosIdx;

	int _maxFramX;
	int _prevFrameY;

	int _curHP;
	int _maxHP;
	int _power;
	int _coinCount;

	int _beatCount;
	int _prevBeatCount;

	float _count;
	float _effectCount;

	bool _isLeft;
	bool _isMove;
	bool _isAttack;

public:
	virtual HRESULT init(int idxY, int idxX);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	Vec2 getPosIdx() { return _posIdx; }
	void setPosIdx(int idxX, int idxY) { _posIdx.x = idxX, _posIdx.y = idxY; }

	Vec2 getNextPosIdx() { return _nextPosIdx; }
	void setNextPosIdx(int idxX, int idxY) { _nextPosIdx.x = idxX, _nextPosIdx.y = idxY; }

	int getCurHP() { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }

	int getCoinCount() { return _coinCount; }

	Enemy() {}
	virtual ~Enemy() {}
};

