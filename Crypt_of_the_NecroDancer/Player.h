#pragma once
#include "SingletonBase.h"
#include "Shovel.h"
#include "Weapon.h"
#include "Armor.h"

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
	GImage* _headImg;						// 플레이어 머리 이미지
	GImage* _bodyImg;						// 플레이어 몸통 이미지

	Shovel* _curShovel;						// 플레이어가 착용 중인 삽
	Weapon* _curWeapon;						// 플레이어가 착용 중인 무기
	Armor _curArmor;						// 플레이어가 착용 중인 갑옷

	POINTFLOAT _pos;						// 현재 플레이어 포지션
	int _posIdxX;							// 현재 플레이어가 있는 타일인덱스 X
	int _posIdxY;							// 현재 플레이어가 있는 타일인덱스 Y

	RECT _rc;								// 플레이어 충돌체

	PLAYER_DIRECTION _curDirection;			// 플레이어 방향 정보

	int _maxHP;								// 플레이어 최대 체력
	int _curHP;								// 플레이어 현재 체력
	int _lightPower;						// 불빛의 세기

	int _coin;								// 플레이어 보유 코인
	int _diamond;							// 플레이어 보유 다이아몬드

	bool _isMove;							// 움직이고 있는 상태인지
	bool _isLeft;							// 왼쪽을 바라보고 있는 상태인지

	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);
	void showShovel(PLAYER_DIRECTION direction, HDC hdc);
	void showAttackEffect(PLAYER_DIRECTION direction, HDC hdc);


	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	int getPosIdxX() { return _posIdxX; }
	void setPosIdxX(int idxX) { _posIdxX = idxX; }

	int getPosIdxY() { return _posIdxY; }
	void setPosIdxY(int idxY) { _posIdxY = idxY; }

	int getCoin() { return _coin; }
	int getDiamond() { return _diamond; }

	void setMaxHP(int maxHP) { _maxHP = maxHP; }
	int getMaxHP() { return _maxHP; }

	void setCurHP(int curHP) { _curHP = curHP; }
	int getCurHP() { return _curHP; }

	void setLightPower(int lightPower) { _lightPower = lightPower; }
	int getLightPower() { return _lightPower; }

	PLAYER_DIRECTION getCurDirection() { return _curDirection; }
	void setCurDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }

	Shovel* getCurShovel() { return _curShovel; }
	Weapon* getCurWeapon() { return _curWeapon; }

	Player() {}
	~Player() {}
};

