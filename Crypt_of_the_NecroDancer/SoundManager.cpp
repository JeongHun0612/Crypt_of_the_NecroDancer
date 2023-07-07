#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr)
							,  _channel(nullptr)
							,  _sound(nullptr)
{
}


HRESULT SoundManager::init()
{
	// 사운드 시스템 생성
	System_Create(&_system);

	// 시스템 초기화
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	// 채널 수 만큼 메모리 버퍼 및 사운드 생성
	_sound = new Sound * [TOTALSOUNDBUFFER];
	_channel = new Channel * [TOTALSOUNDBUFFER];

	// 메모리 초기화
	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void SoundManager::release()
{
	// 사운드 삭제
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
	
	// 시스템 해제
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
			// 통로를 만들어주기 떄문에 createStream
			// 1 : 1 매칭
			// createStream(파일명, 사운드를 열기 위한 방식, 성공 여부 반환, 주소값)
			_system->createStream(fileName, FMOD_LOOP_NORMAL, NULL, &_sound[_mSoundList.size()]);
		}
		else
		{
			// 안전성은 떨어지지만 동시에 여러 개의 음원 재생 가능
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
