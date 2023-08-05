#pragma once
#include "../DesingPattern/SingletonBase.h"

#define	KEY_MAX	256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	HRESULT init(void);

	bool isOnceKeyDown(int key);	// 키가 한번만 눌렸는지
	bool isOnceKeyUp(int key);		// 한번 누르고 띄었는지
	bool isStayKeyDown(int key);	// 키가 계속 눌려 있는지
	bool isToggleKey(int key);		// 토글키
	bool isAnyKeyDown();			// 아무키나 입력했을 시

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager() {}
	~KeyManager() {}
};

