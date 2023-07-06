#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	RECT rc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void addImage();

	MainGame() {}
	~MainGame() {}
};