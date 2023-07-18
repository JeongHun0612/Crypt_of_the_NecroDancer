#pragma once

class Slime
{
protected:
	GImage* _img;

	int _idxX;
	int _idxY;
	int _heart;
	bool _isAttack;

	float _count;

public:
	virtual HRESULT init(int idxX, int idxY, int heart);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	int getIdxX() { return _idxX; }
	int getIdxY() { return _idxY; }

	Slime() {}
	~Slime() {}
};

