#pragma once
#include "../DesingPattern/SingletonBase.h"

//#include "inc/fmod.hpp"
//#pragma comment(lib, "lib/fmodex64_vc.lib")


#include "../../../03_Library/inc/fmod.hpp"

//#pragma comment(lib, "../../../03_Library/lib/fmodex64_vc.lib")
#pragma comment(lib, "03_Library/lib/fmodex64_vc.lib")


using namespace FMOD;

// 사운드 버퍼를 총 30개 + 10개의 여유분으로 준비
#define SOUNDBUFFER 30
#define EXTRACHANNELBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletonBase<SoundManager>
{
private:
	struct ChannelInfo
	{
		string soundName;
		Channel* chaneel;
	};

	typedef map<string, Sound*>					mapSoundList;
	typedef map<string, Sound*>::iterator		mapSoundIter;

private:
	// FMOD를 사용하기 위한 시작지점, 끝지점
	System* _system;

	// 사운드 리스트
	mapSoundList _mSoundList;

	// 현재 활성화된 채널
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

	unsigned int getLength(string strKey);

	SoundManager();
	~SoundManager() {}
};

