#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// GetTickCount() : API 공용 함수
		// ㄴ API 함수로 OS가 부팅된 후의 경과 시간을 체크해 준다.
		// ㄴ 밀리세컨 단위로 체크가 가능하며 밀리세컨 단위로 시간 값을 반환하기 때문에 규모가 크지 않은 로직에 적합하다.
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init(void) { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	// 0을 조심하자.
	inline int getFromIntTo(int fromNum, int toNum)
	{
		// fromNum 과 toNum의 차이의 대한 예외처리를 해야 하지만 조건식이 들어가면 inline화가 되지 않을 가능성이있다.
		// ㄴ 또한 프로그래머가 함수를 사용하기 때문에 예외가 되는 매개변수를 넘기지 않을것이다.
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}
};