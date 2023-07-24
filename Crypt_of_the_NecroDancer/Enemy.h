#pragma once

enum ENEMY_DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

class Enemy
{
protected:
	// Left - Right - Up - Down
	Vec2 _fourDirection[4] =
	{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	GImage* _img;
	GImage* _shadowImg;
	GImage* _heartImg;
	GImage* _effectImg;

	vector<Tile*> _vStage1Wall;

	Vec2_F _pos;
	Vec2 _posIdx;
	Vec2 _nextPosIdx;

	int _distance;

	int _maxFramX;
	int _prevFrameY;

	int _curHP;
	int _maxHP;
	int _power;
	int _coinCount;

	int _stepCount;
	int _beatCount;
	int _prevBeatCount;

	float _count;
	float _effectCount;
	float _jumpPower;

	bool _isLeft;
	bool _isMove;
	bool _isAttack;
	bool _isDie;

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

	bool getIsDie() { return _isDie; }

	Enemy() {}
	virtual ~Enemy() {}
};

