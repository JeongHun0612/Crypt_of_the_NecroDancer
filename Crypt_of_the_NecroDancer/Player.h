#pragma once
#include "SingletonBase.h"
#include "Shovel.h"
#include "Weapon.h"
#include "Armor.h"

enum class PLAYER_DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

class Player : public SingletonBase<Player>
{
private:

	GImage* _headImg;						// 플레이어 머리 이미지
	GImage* _bodyImg;						// 플레이어 몸통 이미지
	GImage* _shadowImg;						// 플레이어 그림자 이미지

	RECT _rc;								// 플레이어 충돌체

	PLAYER_DIRECTION _curDirection;			// 플레이어 방향 정보
	PLAYER_DIRECTION _nextDirection;		// 플레이어 다음 방향 정보

	Shovel* _curShovel;						// 플레이어가 착용 중인 삽
	Weapon* _curWeapon;						// 플레이어가 착용 중인 무기
	Armor _curArmor;						// 플레이어가 착용 중인 갑옷

	POINTFLOAT _pos;						// 현재 플레이어 포지션
	int _posIdxX;							// 현재 플레이어가 있는 타일인덱스 X
	int _posIdxY;							// 현재 플레이어가 있는 타일인덱스 Y

	int _nextIdxX;							// 플레이어의 다음 행동 좌표 X
	int _nextIdxY;							// 플레이어의 다음 행동 좌표 Y

	float _jumpPower;						// 점프 강도

	int _maxHP;								// 플레이어 최대 체력
	int _curHP;								// 플레이어 현재 체력
	int _lightPower;						// 불빛의 세기
	int _effectAlpha;						// 피격 이펙트 알파값
	int _shadowAlpha;						// 그림자 알파값

	int _coin;								// 플레이어 보유 코인
	int _diamond;							// 플레이어 보유 다이아몬드

	bool _isMove;							// 움직이고 있는 상태인지
	bool _isLeft;							// 왼쪽을 바라보고 있는 상태인지
	bool _isHit;							// 플레이어가 피격 상태인지

	float _count;

public:
	HRESULT init(int startIdxX, int startIxY);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveAction(PLAYER_DIRECTION direction);

	// 플레이어 포지션
	POINTFLOAT	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	int getPosIdxX() { return _posIdxX; }
	void setPosIdxX(int idxX) { _posIdxX = idxX; }

	int getPosIdxY() { return _posIdxY; }
	void setPosIdxY(int idxY) { _posIdxY = idxY; }

	int getNextIdxX() { return _nextIdxX; }
	void setNextIdxX(int idxX) { _nextIdxX = idxX; }

	int getNextIdxY() { return _nextIdxY; }
	void setNextIdxY(int idxY) { _nextIdxY = idxY; }


	// 플레이어 재화
	void setCoin(int coin) { _coin = coin; }
	int getCoin() { return _coin; }
	int getDiamond() { return _diamond; }


	// 플레이어 체력
	void setMaxHP(int maxHP) { _maxHP = maxHP; }
	int getMaxHP() { return _maxHP; }

	void setCurHP(int curHP) { _curHP = curHP; }
	int getCurHP() { return _curHP; }


	// 플레이어 그림자 알파값
	void setShadowAlpha(int alpha) { _shadowAlpha = alpha; }


	// 플레이어 시야 범위
	void setLightPower(int lightPower) { _lightPower = lightPower; }
	int getLightPower() { return _lightPower; }


	// 플레이어 상하좌우 상태
	PLAYER_DIRECTION getCurDirection() { return _curDirection; }
	void setCurDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	PLAYER_DIRECTION getNextDirection() { return _nextDirection; }
	void setNextDirection(PLAYER_DIRECTION direction) { _nextDirection = direction; }


	// 플레이어 상태 변수
	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsMove() { return _isMove; }
	void setIsHit(bool isHit) { _isHit = isHit; }


	// 플레이어 소지 장비
	Shovel* getCurShovel() { return _curShovel; }
	Weapon* getCurWeapon() { return _curWeapon; }

	Player() {}
	~Player() {}
};

