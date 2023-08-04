#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _title;
	GImage* _anyKey;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	TitleScene() {}
	~TitleScene() {}
};

