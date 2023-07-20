#pragma once
#include "SingletonBase.h"

enum class INVENTORY_TYPE
{
	SHOVEL,
	ATTACK,
	BODY,

	END
};

enum class HEART_TYPE
{
	EMPTY,
	HALF,
	FULL
};

struct Inventory
{
	GImage* img;
	INVENTORY_TYPE type;
	int x, y;
};

struct Coin
{
	GImage* img;
	int x, y;
	int coinCount;
};

struct Heart
{
	GImage* img;
	int x, y;
};

class UIManager : public SingletonBase<UIManager>
{
private:
	vector<Inventory> _vInventory;
	vector<Heart> _vHeart;
	vector<Coin> _vCoin;

	int _prevHP;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addCoin(int idxX, int idxY, int coinCount);

	vector<Inventory>& getInventory() { return _vInventory; }
};

