#pragma once
#include "SingletonBase.h"

// ���� ����
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*>			 mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;		// ���� ��
	mapSceneList _mSceneList;			// �� ���

public:
	HRESULT init();
	void release();
	void update();
	void render();

	GameNode* addScene(string sceneName, GameNode* scene);

	HRESULT changeScene(string sceneName);

	SceneManager() {}
	~SceneManager() {}
};

