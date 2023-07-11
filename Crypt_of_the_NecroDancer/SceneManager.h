#pragma once
#include "SingletonBase.h"

// Àü¹æ ¼±¾ð
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*>			 mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	GameNode* _currentScene;			// ÇöÀç ¾À
	mapSceneList _mSceneList;			// ¾À ¸ñ·Ï

public:
	HRESULT init();
	void release();
	void update();
	void render();

	GameNode* addScene(string sceneName, GameNode* scene);

	HRESULT changeScene(string sceneName);

	SceneManager() : _currentScene(nullptr) {}
	~SceneManager() {}
};

