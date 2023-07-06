#pragma once
#include "SingletonBase.h"

#pragma comment(lib, "Library/lib/x64/fmod_vc")
#include "Library/inc/fmod.hpp"

class SoundManager : public SingletonBase<SoundManager>
{
private:

public:
	HRESULT init();
	void release();
	void update();

	SoundManager() {}
	~SoundManager() {}
};

