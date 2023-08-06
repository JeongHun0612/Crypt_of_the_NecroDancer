#pragma once

#include "../../../2DFrameWork/DesingPattern/SingletonBase.h"
#include "../Enemy/Enemy.h"
#include "../Item/Shovel/Shovel.h"
#include "../Item/Weapon/Weapon.h"
#include "../Item/Armor/Armor.h"
#include "../Item/Potion/Potion.h"
#include "../Item/Bomb/Bomb.h"

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
	// Left - RIGHT - UP - DOWN
	Vec2 _fourDirection[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	vector<vector<Tile*>> _vTiles;			// 타일 정보

	vector<Tile*> _vTerrainTile;			// 바닥 타일 정보
	vector<Tile*> _vWallTile;				// 벽 타일 정보
	vector<Enemy*> _vEnemy;					// 적 정보
	vector<Item*> _vItem;					// 아이템 정보

	int _tileMaxCol;						// 타일 최대 가로 길이

	GImage* _headImg;						// 플레이어 머리 이미지
	GImage* _bodyImg;						// 플레이어 몸통 이미지
	GImage* _shadowImg;						// 플레이어 그림자 이미지
	AlphaImage _freezingImg;				// 빙결 이미지

	PLAYER_DIRECTION _curDirection;			// 플레이어 방향 정보
	PLAYER_DIRECTION _nextDirection;		// 플레이어 다음 방향 정보

	vector<Shovel> _vShowShovel;
	Shovel* _curShovel;						// 플레이어가 착용 중인 삽
	Weapon* _curWeapon;						// 플레이어가 착용 중인 무기
	Armor* _curArmor;						// 플레이어가 착용 중인 갑옷
	Potion* _curPotion;						// 플레이어가 소지 중인 포션
	Bomb* _curBomb;							// 플레이어가 소지 중인 폭탄

	Vec2_F _pos;							// 현재 플레이어 포지션
	Vec2 _posIdx;							// 현재 플레이어가 있는 타일 인덱스
	Vec2 _nextPosIdx;						// 플레이어의 다음 행동 타일 인덱스

	int _maxHP;								// 플레이어 최대 체력
	int _curHP;								// 플레이어 현재 체력
	int _stepCount;							// 스탭 카운트
	int _beatCount;							// 비트 카운트
	int _prevBeatCount;						// 이전 비트 카운트
	int _lightPower;						// 불빛의 세기
	int _playerAlpha;						// 플레이어 알파값
	int _shadowAlpha;						// 그림자 알파값
	int _effectAlpha;						// 피격 이펙트 알파값

	int _coin;								// 플레이어 보유 코인
	int _diamond;							// 플레이어 보유 다이아몬드

	bool _isMove;							// 움직이고 있는 상태인지
	bool _isLeft;							// 왼쪽을 바라보고 있는 상태인지
	bool _isAttack;							// 플레이어가 공격 상태인지
	bool _isHit;							// 플레이어가 피격 상태인지
	bool _isBomb;							// 플레이어가 폭탄을 사용했는지
	bool _isInvincible;						// 플레이어가 무적 상태인지
	bool _isGrab;							// 원숭이가 매달린 상태인지
	bool _isIce;							// 플레이어가 빙결 상태인지
	bool _isNextStage;						// 다음 스테이지로 넘어갈 수 있는 조건이 갖춰줬는지


	float _count;							// 프레임 이미지 카운트
	float _jumpPower;						// 점프 강도
	float _speed;							// 플레이어 속도

public:
	HRESULT init();
	HRESULT init(int startIdxX, int startIdxY, vector<vector<Tile*>>& vTiles);
	HRESULT init(int startIdxX, int startIdxY, vector<Enemy*>& vEnemy, vector<Item*>& vItem, vector<vector<Tile*>>& vTiles, int tileMaxCol);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addShowShovel(int idxX, int idxY);

	// 플레이어 포지션
	Vec2_F	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	Vec2 getPosIdx() { return _posIdx; }
	void setPosIdx(int x, int y) { _posIdx.x = x, _posIdx.y = y; }

	Vec2 getNextPosIdx() { return _nextPosIdx; }
	void setNextPosIdx(int x, int y) { _nextPosIdx.x = x, _nextPosIdx.y = y; }


	// 플레이어 재화
	int getCoin() { return _coin; }
	void setCoin(int coin) { _coin = coin; }

	int getDiamond() { return _diamond; }
	void setDiamond(int diamond) { _diamond = diamond; }


	// 플레이어 체력
	int getMaxHP() { return _maxHP; }
	void setMaxHP(int maxHP) { _maxHP = maxHP; }

	int getCurHP() { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }

	// 플레이어 알파값
	int getPlayerAlpha() { return _playerAlpha; }
	void setPlayerAlpha(int alpha) { _playerAlpha = alpha; }

	void setShadowAlpha(int alpha) { _shadowAlpha = alpha; }

	// 플레이어 스탭 카운트
	void setStepCount(int stepCount) { _stepCount = stepCount; }


	// 플레이어 시야 범위
	int getLightPower() { return _lightPower; }
	void setLightPower(int lightPower) { _lightPower = lightPower; }


	// 플레이어 상하좌우 상태
	PLAYER_DIRECTION getCurDirection() { return _curDirection; }
	void setCurDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	PLAYER_DIRECTION getNextDirection() { return _nextDirection; }
	void setNextDirection(PLAYER_DIRECTION direction) { _nextDirection = direction; }


	// 플레이어 상태 변수
	bool getIsMove() { return _isMove; }
	void setIsMove(bool isMove) { _isMove = isMove; }

	void setIsHit(bool isHit) { _isHit = isHit; }

	void setIsInvincible(bool isInvincible) { _isInvincible = isInvincible; }
	bool getIsInvincible() { return _isInvincible; }

	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }

	bool getIsBomb() { return _isBomb; }
	void setIsBomb(bool isBomb) { _isBomb = isBomb; }

	void setIsGrab(bool isGrab) { _isGrab = isGrab; }

	bool setIsIce(bool isIce) { return _isIce = isIce; }

	bool getIsNextStage() { return _isNextStage; }
	void setIsNextStage(bool isNextStage) { _isNextStage = isNextStage; }



	// 플레이어 소지 장비
	Shovel* getCurShovel() { return _curShovel; }
	void setCurShovel(Shovel* curShovel) { _curShovel = curShovel; }

	Weapon* getCurWeapon() { return _curWeapon; }
	void setCurWeapon(Weapon* curWeapon) { _curWeapon = curWeapon; }

	Armor* getCurArmor() { return _curArmor; }
	void setCurArmor(Armor* curArmor) { _curArmor = curArmor; }

	Potion* getCurPotion() { return _curPotion; }
	void setCurPotion(Potion* curPotion) { _curPotion = curPotion; }

	Bomb* getCurBomb() { return _curBomb; }
	void setCurBomb(Bomb* curBomb) { _curBomb = curBomb; }

	Player() {}
	~Player() {}
};

