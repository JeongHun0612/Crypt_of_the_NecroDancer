#pragma once
#include "SingletonBase.h"

//#pragma comment(lib, "core/lib/x64/fmod_vc.lib")
//#include "fmod.hpp"

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

// ���� ���۸� �� 30�� + 10���� ���������� �غ�
#define SOUNDBUFFER 30
#define EXTRACHANNELBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletonBase<SoundManager>
{
private:
	//typedef map<string, Sound**>				mapSoundList;
	//typedef map<string, Sound**>::iterator		mapSoundIter;
	//typedef map<string, Channel**>				mapChannelList;
	//typedef map<string, Channel**>::iterator	mapChannelIter;

	struct ChannelInfo
	{
		string soundName;
		Channel* chaneel;
	};

	typedef map<string, Sound*>					mapSoundList;
	typedef map<string, Sound*>::iterator		mapSoundIter;

private:
	// FMOD�� ����ϱ� ���� ��������, ������
	System* _system;

	// ���� ����Ʈ
	mapSoundList _mSoundList;

	// ���� Ȱ��ȭ�� ä��
	vector<ChannelInfo> _mActiveChannels;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string strKey, const char* fileName, bool bgm, bool loop);

	void play(string strKey, float volume = 1.0f);
	void stop(string strKey);
	void pause(string strKey);

	unsigned int getPosition(string strKey);
	void setPosition(string strKey, float pos);

	float getVolume(string strKey);
	void setVolume(string strKey, float volume);

	SoundManager();
	~SoundManager() {}
};

