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

	vector<vector<Tile*>> _vTiles;			// Ÿ�� ����

	vector<Tile*> _vTerrainTile;			// �ٴ� Ÿ�� ����
	vector<Tile*> _vWallTile;				// �� Ÿ�� ����
	vector<Enemy*> _vEnemy;					// �� ����
	vector<Item*> _vItem;					// ������ ����

	int _tileMaxCol;						// Ÿ�� �ִ� ���� ����

	GImage* _headImg;						// �÷��̾� �Ӹ� �̹���
	GImage* _bodyImg;						// �÷��̾� ���� �̹���
	GImage* _shadowImg;						// �÷��̾� �׸��� �̹���
	AlphaImage _freezingImg;				// ���� �̹���

	PLAYER_DIRECTION _curDirection;			// �÷��̾� ���� ����
	PLAYER_DIRECTION _nextDirection;		// �÷��̾� ���� ���� ����

	vector<Shovel> _vShowShovel;
	Shovel* _curShovel;						// �÷��̾ ���� ���� ��
	Weapon* _curWeapon;						// �÷��̾ ���� ���� ����
	Armor* _curArmor;						// �÷��̾ ���� ���� ����
	Potion* _curPotion;						// �÷��̾ ���� ���� ����
	Bomb* _curBomb;							// �÷��̾ ���� ���� ��ź

	Vec2_F _pos;							// ���� �÷��̾� ������
	Vec2 _posIdx;							// ���� �÷��̾ �ִ� Ÿ�� �ε���
	Vec2 _nextPosIdx;						// �÷��̾��� ���� �ൿ Ÿ�� �ε���

	int _maxHP;								// �÷��̾� �ִ� ü��
	int _curHP;								// �÷��̾� ���� ü��
	int _stepCount;							// ���� ī��Ʈ
	int _beatCount;							// ��Ʈ ī��Ʈ
	int _prevBeatCount;						// ���� ��Ʈ ī��Ʈ
	int _lightPower;						// �Һ��� ����
	int _playerAlpha;						// �÷��̾� ���İ�
	int _shadowAlpha;						// �׸��� ���İ�
	int _effectAlpha;						// �ǰ� ����Ʈ ���İ�

	int _coin;								// �÷��̾� ���� ����
	int _diamond;							// �÷��̾� ���� ���̾Ƹ��

	bool _isMove;							// �����̰� �ִ� ��������
	bool _isLeft;							// ������ �ٶ󺸰� �ִ� ��������
	bool _isAttack;							// �÷��̾ ���� ��������
	bool _isHit;							// �÷��̾ �ǰ� ��������
	bool _isBomb;							// �÷��̾ ��ź�� ����ߴ���
	bool _isInvincible;						// �÷��̾ ���� ��������
	bool _isGrab;							// �����̰� �Ŵ޸� ��������
	bool _isIce;							// �÷��̾ ���� ��������
	bool _isNextStage;						// ���� ���������� �Ѿ �� �ִ� ������ ���������


	float _count;							// ������ �̹��� ī��Ʈ
	float _jumpPower;						// ���� ����
	float _speed;							// �÷��̾� �ӵ�

public:
	HRESULT init();
	HRESULT init(int startIdxX, int startIdxY, vector<vector<Tile*>>& vTiles);
	HRESULT init(int startIdxX, int startIdxY, vector<Enemy*>& vEnemy, vector<Item*>& vItem, vector<vector<Tile*>>& vTiles, int tileMaxCol);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addShowShovel(int idxX, int idxY);

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

	// �÷��̾� ���İ�
	int getPlayerAlpha() { return _playerAlpha; }
	void setPlayerAlpha(int alpha) { _playerAlpha = alpha; }

	void setShadowAlpha(int alpha) { _shadowAlpha = alpha; }

	// �÷��̾� ���� ī��Ʈ
	void setStepCount(int stepCount) { _stepCount = stepCount; }


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



	// �÷��̾� ���� ���
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

