#pragma once

enum ENEMY_DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

struct MoveInfo
{
	int direction;
	int distance;
};

class Enemy
{
protected:
	// Left - Right - Up - Down
	Vec2 _fourDirection[4] =
	{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	ENEMY_TYPE _type;

	FrameImage _img;
	FrameImage _effectImg;
	AlphaImage _shadowImg;
	GImage* _heartImg;

	vector<vector<Tile*>> _vTiles;
	vector<Tile*> _vTerrainTile;
	vector<Tile*> _vWallTile;

	int _maxTileCol;
	int _curTileIdx;
	int _nextTileIdx;

	Vec2_F _pos;
	Vec2 _posIdx;
	Vec2 _nextPosIdx;

	MoveInfo _moveInfo[4];

	int _distance;
	int _curMoveDirection;
	int _alpha;

	int _curHP;
	int _maxHP;
	int _power;
	int _coinCount;

	int _stepCount;
	int _beatCount;
	int _prevBeatCount;
	int _skillPattern;

	float _jumpPower;
	float _frameCycle;

	bool _isLeft;
	bool _isMove;
	bool _isHit;
	bool _isCry;
	bool _isAttack;
	bool _isSkill;
	bool _isInvincible;

public:
	virtual HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// 오름차순 정렬 함수
	void sortDistance(MoveInfo* moveInfo, int num, bool ASC);

	// 적 포지션
	Vec2 getPosIdx() { return _posIdx; }
	void setPosIdx(int idxX, int idxY) { _posIdx.x = idxX, _posIdx.y = idxY; }

	Vec2 getNextPosIdx() { return _nextPosIdx; }
	void setNextPosIdx(int idxX, int idxY) { _nextPosIdx.x = idxX, _nextPosIdx.y = idxY; }

	void setCurTileIdx(int curTileIdx) { _curTileIdx = curTileIdx; }

	// 적 타입
	ENEMY_TYPE getEnemyType() { return _type; }

	// 적 HP
 	int getCurHP() { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }

	// 스킬 패턴
	int getSkillPattern() { return _skillPattern; }

	// 적 보유 코인
	int getCoinCount() { return _coinCount; }

	// 적 상태
	bool getIsHit() { return _isHit; }
	void setIsHit(bool isHit) { _isHit = isHit; }

	bool getIsSkill() { return _isSkill; }
	void setIsSkill(bool isSKill) { _isSkill = isSKill; }

	bool getIsInvincible() { return _isInvincible; }

	Enemy() {}
	virtual ~Enemy() {}
};

