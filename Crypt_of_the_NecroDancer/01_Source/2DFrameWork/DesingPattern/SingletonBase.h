#pragma once

template <class T>
class SingletonBase
{
protected:
	// 싱글톤 인스턴스
	static T* singleTon;

	SingletonBase() {}
	~SingletonBase() {}

public:
	// 싱글톤 가져오기
	static T* getSingleton(void);

	// 싱글톤 메모리에서 해제
	void releaseSingleton(void);
};

// 싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleTon = 0;

// 싱글톤 가져오기
template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleTon) singleTon = new T;

	return singleTon;
}

// 싱글톤 메모리 해제
template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	// 싱글톤이 있다면 메모리에서 해제
	if (singleTon)
	{
		delete(singleTon);
		singleTon = 0;
	}
}