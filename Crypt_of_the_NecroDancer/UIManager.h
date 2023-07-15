#pragma once
#include "SingletonBase.h"

class UIManager : public SingletonBase<UIManager>
{
private:
	enum class ITEM_TYPE
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
		ITEM_TYPE type;
		int x, y;
	};

	struct Heart
	{
		GImage* img;
		int x, y;
	};

private:
	vector<Inventory> _vInventory;
	vector<Heart> _vHeart;

	int _prevHP;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
};

