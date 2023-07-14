#pragma once
#include "SingletonBase.h"

class Beat : public SingletonBase<Beat>
{
private:
	enum NOTE_DISTANCE
	{
		LEFT,
		RIGHT
	};

	struct Note
	{
		GImage* img;
		RECT rc;

		int alpha;

		float x, y;
		float speed;

		bool isDestory;
	};

	struct FrameImage
	{
		GImage* img;
		RECT rc;

		float x, y;
		int frameX;
		int frameY;
		float frameCount;
	};

	struct Missed
	{
		GImage* img;
		float x, y;
		int alpha;
	};

private:
	vector<Note> _vNoteLeft;			// 왼쪽 노트 벡터
	vector<Note> _vNoteRight;			// 오른쪽 노트 벡터

	queue<int> _qNoteData;				// 박자 정보가 담긴 데이터
	unsigned int _noteCycle;			// 노트가 생성되는 주기

	FrameImage _heartRate;				// 심장박동 이미지
	POINT _eraseLine;					// 심장박동 이미지 가운데는 노트 삭제 라인

	vector<Missed> _vMissed;			// 빗나감 이미지 벡터
	GImage* _missedImg;					// 빗나감 이미지
	int _missedAlpha;					// 빗나감 이미지 알파값

	bool _isBeat;						// 박자가 맞는지
	bool _isMusic;						// 현재 음악이 재생되고 있는지
	bool _isMissed;						// 박자에 맞춰 키 입력에 실패했는지
	bool _isSuccess;					// 박자에 맞춰 키 입력에 성공했는지

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);

	void createNote();

	void createMissed();
	void moveMissed();

	bool getBeat() { return _isBeat; }

	bool getIsMissed() { return _isMissed; }
	void setIsMissed(bool isMissed) { _isMissed = isMissed; }

	bool getIsSuccess() { return _isSuccess; }
	void setIsSuccess(bool isSuccess) { _isSuccess = isSuccess; }

	Beat() {}
	~Beat() {}
};

