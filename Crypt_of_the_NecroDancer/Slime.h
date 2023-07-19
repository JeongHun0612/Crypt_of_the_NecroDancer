#pragma once

enum class ENEMY_DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Slime
{
protected:
	GImage* _img;
	GImage* _heartImg;
	GImage* _effectImg;

	ENEMY_DIRECTION _attackDirection;

	int _posX;
	int _posY;

	int _idxX;
	int _idxY;

	int _nextIdxX;
	int _nextIdxY;

	int _curHP;
	int _maxHP;
	int _power;
	int _coinCount;

	int _beatCount;
	int _prevBeatCount;

	float _count;
	float _effectCount;

	bool _isAttack;
	bool _isMove;

public:
	virtual HRESULT init(int idxX, int idxY, int maxHP, int power, int coinCount);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	int getIdxX() { return _idxX; }
	int getIdxY() { return _idxY; }

	int getCurHP() { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }

	int getCoinCount() { return _coinCount; }

	Slime() {}
	~Slime() {}
};

