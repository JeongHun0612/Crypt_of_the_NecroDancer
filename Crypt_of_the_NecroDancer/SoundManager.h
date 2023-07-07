#pragma once
#include "SingletonBase.h"

//#pragma comment(lib,"../03_Libraries/lib/fmodex64_vc")
#pragma comment(lib, "Library/lib/FMOD/fmodex64_vc")
#include "Library/inc/FMOD/fmod.hpp"

using namespace FMOD;


// 사운드 버퍼를 총 20개 + 5개의 여유분으로 준비
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
	// FMOD를 사용하기 위한 시작지점, 끝지점
	System* _system;

	// 더블 포인터인 이유
	// 프로젝트->FMOD(hpp)의 가상함수 -> 코어 로 두 번 건너뛰기 때문이다.
	Sound** _sound;
	Channel** _channel;

	// 사운드 리스트
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

