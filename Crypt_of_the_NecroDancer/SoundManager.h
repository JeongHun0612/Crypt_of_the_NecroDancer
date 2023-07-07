#pragma once
#include "SingletonBase.h"

//#pragma comment(lib,"../03_Libraries/lib/fmodex64_vc")
#pragma comment(lib, "Library/lib/FMOD/fmodex64_vc")
#include "Library/inc/FMOD/fmod.hpp"

using namespace FMOD;


// ���� ���۸� �� 20�� + 5���� ���������� �غ�
#define SOUNDBUFFER 20
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
	// ������Ʈ->FMOD(hpp)�� �����Լ� -> �ھ� �� �� �� �ǳʶٱ� �����̴�.
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

	SoundManager();
	~SoundManager() {}
};

