#pragma once
#include "SingletonBase.h"

enum class PLAYER_DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class Player : public SingletonBase<Player>
{
private:
	struct Shovel
	{
		GImage* img;
		int hardness;
	};


private:
	GImage* _headImg;						// 플레이어 머리 이미지
	GImage* _bodyImg;						// 플레이어 몸통 이미지

	GImage* _weaponItemImg;

	POINTFLOAT _pos;						// 현재 플레이어 포지션
	POINT _posIdx;							// 현재 플레이어가 있는 타일번호

	RECT _rc;								// 플레이어 충돌체

	PLAYER_DIRECTION _curDirection;			// 플레이어 방향 정보

	Shovel _curShovel;						// 플레이어 현재 장착중인 삽

	int _maxHP;								// 플레이어 최대 체력
	int _curHP;								// 플레이어 현재 체력

	int _coin;								// 플레이어 보유 코인
	int _diamond;							// 플레이어 보유 다이아몬드

	bool _isMove;
	bool _isLeft;

	bool _isShovel;

	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	POINT getPosIdx() { return _posIdx; }
	void setPosIdx(int x, int y) { _posIdx.x = x, _posIdx.y = y; }

	int getCoin() { return _coin; }
	int getDiamond() { return _diamond; }

	void setMaxHP(int maxHP) { _maxHP = maxHP; }
	int getMaxHP() { return _maxHP; }

	void setCurHP(int curHP) { _curHP = curHP; }
	int getCurHP() { return _curHP; }

	void setDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }

	void setIsShovel(bool isShovel) { _isShovel = isShovel; }
	bool getIsShovel() { return _isShovel; }


	Shovel getShovel() { return _curShovel; }

	Player() {}
	~Player() {}
};

