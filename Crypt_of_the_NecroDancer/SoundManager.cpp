#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr)
							,  _channel(nullptr)
							,  _sound(nullptr)
{
}


HRESULT SoundManager::init()
{
	// ���� �ý��� ����
	System_Create(&_system);

	// �ý��� �ʱ�ȭ
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	// ä�� �� ��ŭ �޸� ���� �� ���� ����
	_sound = new Sound * [TOTALSOUNDBUFFER];
	_channel = new Channel * [TOTALSOUNDBUFFER];

	// �޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void SoundManager::release()
{
	// ���� ����
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
 			}

			if (_sound != nullptr)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);
	
	// �ý��� ����
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::update()
{
	_system->update();
}

void SoundManager::addSound(string strKey, const char* fileName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			// ��θ� ������ֱ� ������ createStream
			// 1 : 1 ��Ī
			// createStream(���ϸ�, ���带 ���� ���� ���, ���� ���� ��ȯ, �ּҰ�)
			_system->createStream(fileName, FMOD_LOOP_NORMAL, NULL, &_sound[_mSoundList.size()]);
		}
		else
		{
			// �������� ���������� ���ÿ� ���� ���� ���� ��� ����
			_system->createSound(fileName, FMOD_LOOP_NORMAL, NULL, &_sound[_mSoundList.size()]);
		}
	}
	else
	{
		_system->createStream(fileName, FMOD_DEFAULT, NULL, &_sound[_mSoundList.size()]);
	}

	_mSoundList[strKey] = &_sound[_mSoundList.size()];
}

void SoundManager::play(string strKey, float volume)
{
	mapSoundIter iter = _mSoundList.begin();
	int count = 0;

	for (iter; iter != _mSoundList.end(); ++iter, count++)
	{
		if (strKey == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void SoundManager::stop(string strKey)
{
	mapSoundIter iter = _mSoundList.begin();
	int count = 0;

	for (iter; iter != _mSoundList.end(); ++iter, count++)
	{
		if (strKey == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::pause(string strKey)
{
	mapSoundIter iter = _mSoundList.begin();
	int count = 0;

	for (iter; iter != _mSoundList.end(); ++iter, count++)
	{
		if (strKey == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string strKey)
{
	mapSoundIter iter = _mSoundList.begin();
	int count = 0;

	for (iter; iter != _mSoundList.end(); ++iter, count++)
	{
		if (strKey == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}
