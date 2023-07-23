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

	vector<vector<Tile*>> _vTiles;			// Ÿ�� ����

	vector<Tile*> _vTerrainTile;			// �ٴ� Ÿ�� ����
	vector<Tile*> _vWallTile;				// �� Ÿ�� ����
	vector<Enemy*> _vEnemy;					// �� ����

	int _tileMaxCol;						// Ÿ�� �ִ� ���� ����

	GImage* _headImg;						// �÷��̾� �Ӹ� �̹���
	GImage* _bodyImg;						// �÷��̾� ���� �̹���
	GImage* _shadowImg;						// �÷��̾� �׸��� �̹���

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����
	PLAYER_DIRECTION _nextDirection;		// �÷��̾� ���� ���� ����

	Shovel* _curShovel;						// �÷��̾ ���� ���� ��
	Weapon* _curWeapon;						// �÷��̾ ���� ���� ����
	Armor* _curArmor;						// �÷��̾ ���� ���� ����

	Vec2_F _pos;							// ���� �÷��̾� ������
	Vec2 _posIdx;							// ���� �÷��̾ �ִ� Ÿ�� �ε���
	Vec2 _nextPosIdx;						// �÷��̾��� ���� �ൿ Ÿ�� �ε���

	int _maxHP;								// �÷��̾� �ִ� ü��
	int _curHP;								// �÷��̾� ���� ü��
	int _lightPower;						// �Һ��� ����
	int _effectAlpha;						// �ǰ� ����Ʈ ���İ�
	int _shadowAlpha;						// �׸��� ���İ�

	int _coin;								// �÷��̾� ���� ����
	int _diamond;							// �÷��̾� ���� ���̾Ƹ��

	bool _isMove;							// �����̰� �ִ� ��������
	bool _isLeft;							// ������ �ٶ󺸰� �ִ� ��������
	bool _isAttack;							// �÷��̾ ���� ��������
	bool _isHit;							// �÷��̾ �ǰ� ��������

	float _count;							// ������ �̹��� ī��Ʈ
	float _jumpPower;						// ���� ����

public:
	HRESULT init();
	HRESULT init(int startIdxX, int startIxY);
	HRESULT init(int startIdxX, int startIxY, vector<vector<Tile*>> tiles, int tileMaxCol);
	void release(void);
	void update(void);
	void render(HDC hdc);

	// �÷��̾� ������
	Vec2_F	getPos() { return _pos; }
	void setPos(float x, float y) { _pos.x = x, _pos.y = y; }

	Vec2 getPosIdx() { return _posIdx; }
	void setPosIdx(int x, int y) { _posIdx.x = x, _posIdx.y = y; }

	Vec2 getNextPosIdx() { return _nextPosIdx; }
	void setNextPosIdx(int x, int y) { _nextPosIdx.x = x, _nextPosIdx.y = y; }


	// �÷��̾� ��ȭ
	int getCoin() { return _coin; }
	void setCoin(int coin) { _coin = coin; }

	int getDiamond() { return _diamond; }
	void setDiamond(int diamond) { _diamond = diamond; }


	// �÷��̾� ü��
	int getMaxHP() { return _maxHP; }
	void setMaxHP(int maxHP) { _maxHP = maxHP; }

	int getCurHP() { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }


	// �÷��̾� �׸��� ���İ�
	void setShadowAlpha(int alpha) { _shadowAlpha = alpha; }


	// �÷��̾� �þ� ����
	int getLightPower() { return _lightPower; }
	void setLightPower(int lightPower) { _lightPower = lightPower; }


	// �÷��̾� �����¿� ����
	PLAYER_DIRECTION getCurDirection() { return _curDirection; }
	void setCurDirection(PLAYER_DIRECTION direction) { _curDirection = direction; }

	PLAYER_DIRECTION getNextDirection() { return _nextDirection; }
	void setNextDirection(PLAYER_DIRECTION direction) { _nextDirection = direction; }


	// �÷��̾� ���� ����
	bool getIsMove() { return _isMove; }
	void setIsMove(bool isMove) { _isMove = isMove; }

	void setIsHit(bool isHit) { _isHit = isHit; }

	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }


	// �÷��̾� ���� ���
	Shovel* getCurShovel() { return _curShovel; }
	Weapon* getCurWeapon() { return _curWeapon; }

	void setTile(vector<vector<Tile*>> vTiles) { _vTiles = vTiles; }
	void setTerrainTile(vector<Tile*> vTerrainTile) { _vTerrainTile = vTerrainTile; }
	void setWallTile(vector<Tile*> vWallTile) { _vWallTile = vWallTile; }

	void setTileMaxCol(int tileMaxCol) { _tileMaxCol = tileMaxCol; }

	Player() {}
	~Player() {}
};

