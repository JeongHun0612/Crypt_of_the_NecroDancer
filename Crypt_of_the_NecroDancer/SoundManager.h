#pragma once
#include "SingletonBase.h"

//#pragma comment(lib, "Library/lib/FMOD/fmodex64_vc")
//#include "Library/inc/FMOD/fmod.hpp"

//#pragma comment(lib, "core/lib/x64/fmod_vc.lib")
#include "fmod.hpp"

using namespace FMOD;

// ���� ���۸� �� 30�� + 5���� ���������� �غ�
#define SOUNDBUFFER 30
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**>				mapSoundList;
	typedef map<string, Sound**>::iterator		mapSoundIter;
	typedef map<string, Channel**>				mapChannelList;
	typedef map<string, Channel**>::iterator	mapChannelIter;

private:
	// FMOD�� ����ϱ� ���� ��������, ������
	System* _system;

	// ���� �������� ����
	// ������Ʈ->FMOD(hpp)�� �����Լ� -> �ھ�� �� �� �ǳʶٱ� �����̴�.
	Sound** _sound;
	Channel** _channel;

	// ���� ����Ʈ
	mapSoundList _mSoundList;


public:
	HRESULT init();
	void release();
	void update();

	void addSound(string strKey, const char* fileName, bool bgm, bool loop);

	void play(string strKey, float volume = 1.0f);
	void stop(string strKey);
	void pause(string strKey);
	void resume(string strKey);

	unsigned int getPosition(string strKey);
	void setPosition(string strKey, float pos);

	float getVolume(string strKey);
	void setVolume(string strKey, float volume);

	SoundManager();
	~SoundManager() {}
};

