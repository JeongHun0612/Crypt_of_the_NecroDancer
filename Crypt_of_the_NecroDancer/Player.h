#pragma once
#include "SingletonBase.h"
#include "Enemy.h"
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
	// Left - RIGHT - UP - DOWN
	Vec2 _fourDirection[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	vector<vector<Tile*>> _vTiles;			// 타일 정보

	vector<Tile*> _vTerrainTile;			// 바닥 타일 정보
	vector<Tile*> _vWallTile;				// 벽 타일 정보
	vector<Enemy*> _vEnemy;					// 적 정보

	int _tileMaxCol;						// 타일 최대 가로 길이

	GImage* _headImg;						// 플레이어 머리 이미지
	GImage* _bodyImg;						// 플레이어 몸통 이미지
	GImage* _shadowImg;						// 플레이어 그림자 이미지

	PLAYER_DIRECTION _curDirection;			// 플레이어 방향 정보
	PLAYER_DIRECTION _nextDirection;		// 플레이어 다음 방향 정보

	Shovel* _curShovel;						// 플레이어가 착용 중인 삽
	Weapon* _curWeapon;						// 플레이어가 착용 중인 무기
	Armor* _curArmor;						// 플레이어가 착용 중인 갑옷

	Vec2_F _pos;							// 현재 플레이어 포지션
	Vec2 _posIdx;							// 현재 플레이어가 있는 타일 인덱스
	Vec2 _nextPosIdx;						// 플레이어의 다음 행동 타일 인덱스

	int _maxHP;								// 플레이어 최대 체력
	int _curHP;								// 플레이어 현재 체력
	int _lightPower;						// 불빛의 세기
	int _effectAlpha;						// 피격 이펙트 알파값
	int _shadowAlpha;						// 그림자 알파값

	int _coin;								// 플레이어 보유 코인
	int _diamond;							// 플레이어 보유 다이아몬드

	bool _isMove;							// 움직이고 있는 상태인지
	bool _isLeft;							// 왼쪽을 바라보고 있는 상태인지
	bool _isAttack;							// 플레이어가 공격 상태인지
	bool _isHit;							// 플레이어가 피격 상태인지

	float _count;							// 프레임 이미지 카운트
	float _jumpPower;						// 점프 강도

public:
	HRESULT init();
	HRESULT init(int startIdxX, int startIxY);
	HRESULT init(int startIdxX, int startIxY, vector<vector<Tile*>> tiles, int tileMaxCol);
	void release(void);
	void update(void);
	void render(HDC hdc);

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


	// 플레이어 그림자 알파값
	void setShadowAlpha(int alpha) { _shadowAlpha = alpha; }


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

	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }


	// 플레이어 소지 장비
	Shovel* getCurShovel() { return _curShovel; }
	Weapon* getCurWeapon() { return _curWeapon; }

	void setTile(vector<vector<Tile*>> vTiles) { _vTiles = vTiles; }
	void setTerrainTile(vector<Tile*> vTerrainTile) { _vTerrainTile = vTerrainTile; }
	void setWallTile(vector<Tile*> vWallTile) { _vWallTile = vWallTile; }

	void setTileMaxCol(int tileMaxCol) { _tileMaxCol = tileMaxCol; }

	Player() {}
	~Player() {}
};

