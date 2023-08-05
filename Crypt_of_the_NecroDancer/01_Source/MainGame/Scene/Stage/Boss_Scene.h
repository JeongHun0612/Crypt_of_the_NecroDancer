#pragma once
#include "GameScene.h"

class Boss_Scene : public GameScene
{
private:
	struct CutImage
	{
		GImage* img;
		Vec2 pos;
	};

	CutImage _barImg1;
	CutImage _barImg2;
	CutImage _cutSceneImg;

	Enemy* _necroDancer;
	Enemy* _summonEnemy;

	bool _isCutScene;
	bool _isOpen;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Boss_Scene() {}
	~Boss_Scene() {}
};

