#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

//스태틱 변수인 현재씬을 널 값으로 초기화
GameNode* SceneManager::_currentScene = NULL;

HRESULT SceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void SceneManager::release()
{
	mapSceneIter iter = _mSceneList.begin();

	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)
			{
				iter->second->release();
				SAFE_DELETE(iter->second);
				iter = _mSceneList.erase(iter);
			}
		}
		else
		{
			++iter;
		}
	}

	_mSceneList.clear();
}

void SceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void SceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	// find() 함수로 찾지 못하면 end()값을 반환한다.
	if (find == _mSceneList.end()) return E_FAIL;

	// 바꾸려는 씬이 현재 씬이랑 같을 때
	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		// 기존씬이 존재하면 릴리즈 함수를 실행
		if (_currentScene) _currentScene->release();

		//바꾸려는 씬을 현재씬으로 변경
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
