#pragma once
#include "Item.h"

class Bomb : public Item
{
private:
	Vec2 _explosionRange[8] = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };

	FrameImage _effectImg;

	int _maxTileCol;
	int _power;

	int _stepCount;
	int _beatCount;
	int _prevBeatCount;

	bool _isExplosion;

public:
	HRESULT init();
	HRESULT init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price, int tileMaxCol);
	void release();
	void update();
	void render(HDC hdc);
	void effectRender(HDC hdc);
	void slotRender(HDC hdc, Vec2_F pos);

	bool getIsExplosion() { return _isExplosion; }
	void setIsExplosion(bool isExplosion) { _isExplosion = isExplosion; }

	int getPower() { return _power; }
	
	int getStepCount() { return _stepCount; }
	void setStepCount(int stepCount) { _stepCount = stepCount; }

	Bomb() {}
	~Bomb() {}
};

