#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

//����ƽ ������ ������� �� ������ �ʱ�ȭ
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

	// find() �Լ��� ã�� ���ϸ� end()���� ��ȯ�Ѵ�.
	if (find == _mSceneList.end()) return E_FAIL;

	// �ٲٷ��� ���� ���� ���̶� ���� ��
	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		// �������� �����ϸ� ������ �Լ��� ����
		if (_currentScene) _currentScene->release();

		//�ٲٷ��� ���� ��������� ����
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}