#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "Beat.h"

HRESULT Beat::init()
{
	// 심장 박동 초기화
	_heartImg.img = IMAGEMANAGER->findImage("beat_heart");
	_heartImg.x = WINSIZE_X_HALF - _heartImg.img->getFrameWidth() / 2;
	_heartImg.y = WINSIZE_Y - 130;
	_heartImg.frameX = 0;
	_heartImg.frameY = 0;
	_heartImg.frameCount = 0.0f;

	// 비트 삭제 지점
	_eraseLine = { WINSIZE_X_HALF, WINSIZE_Y - 80 };

	// 비트 성공 범위
	_beatRate = RectMakeCenter(_heartImg.x + _heartImg.img->getFrameWidth() / 2, _heartImg.y + _heartImg.img->getFrameHeight() / 2, 240, 100);

	// 빗나감 이미지 초기화
	_missedImg = IMAGEMANAGER->findImage("missed");
	_missedImg->setX(WINSIZE_X_HALF - _missedImg->getWidth() / 2);
	_missedImg->setY(WINSIZE_Y - 130);
	_missedAlpha = 255;

	// 데이터 초기화
	_beatCount = 0;
	_noteFrameX = 0;


	return S_OK;
}

HRESULT Beat::init(const char* fileName, const char* soundName)
{
	// 노트 정보 불러오기
	FileManager::loadBeatFile(fileName, _vNoteData);
	_soundName = soundName;

	_vNoteLeft.clear();
	_vNoteRight.clear();

	_beatCount = 0;
	_noteFrameX = 0;
	_noteCount = 0;
	_noteCycle = _vNoteData.front();

	_isBeat = false;
	_isStep = false;
	_isMusic = true;
	_isMissed = false;
	_isSuccess = false;

	return S_OK;
}


void Beat::update(void)
{
	// 심장 박동 애니메이션
	_heartImg.frameCount += TIMEMANAGER->getDeltaTime();

	if (_heartImg.frameCount >= 0.276f)
	{
		if (_heartImg.frameX == _heartImg.img->getMaxFrameX())
		{
			_heartImg.frameX = 0;
		}
		else
		{
			_heartImg.frameX++;
		}

		_heartImg.img->setFrameX(_heartImg.frameX);

		_heartImg.frameCount = 0;
	}

	// 노트 생성
	unsigned int soundPos = SOUNDMANAGER->getPosition(_soundName);

	if (_noteCycle <= soundPos && _noteCount < _vNoteData.size() - 1)
	{
		createNote();

		_noteCount++;
		_noteCycle = _vNoteData[_noteCount];

		// 남은 노래 시간이 3/4 일때 비트 색깔 변경
		if (soundPos >= (_vNoteData.back() / 4) * 3 && _soundName != "stage_boss")
		{
			_noteFrameX = 2;
		}

		// 보스 스테이지는 비트 반복
		if (_noteCount == _vNoteData.size() - 1 && _soundName == "stage_boss")
		{
			_noteCount = 0;
			_noteCycle = _vNoteData.front();
			SOUNDMANAGER->setPosition(_soundName, 0);
		}
	}

	// 노트 벡터가 비워지면 노래 끝
	if (_vNoteLeft.empty())
	{
		_isMusic = false;
	}

	for (int i = 0; i < _vNoteLeft.size(); i++)
	{
		// 노트 이동
		_vNoteLeft[i].x += _vNoteLeft[i].speed;
		_vNoteLeft[i].rc = RectMake(_vNoteLeft[i].x, _vNoteLeft[i].y, _vNoteLeft[i].img->getFrameWidth(), _vNoteLeft[i].img->getFrameHeight());

		_vNoteRight[i].x += _vNoteRight[i].speed;
		_vNoteRight[i].rc = RectMake(_vNoteRight[i].x, _vNoteRight[i].y, _vNoteLeft[i].img->getFrameWidth(), _vNoteRight[i].img->getFrameHeight());

		// 알파값 변경
		if (_vNoteLeft[i].alpha < 255)
		{
			_vNoteLeft[i].alpha += 2;
			_vNoteRight[i].alpha += 2;

			if (_vNoteLeft[i].alpha > 255)
			{
				_vNoteLeft[i].alpha = 255;
				_vNoteRight[i].alpha = 255;
			}
		}

		// 노트 키입력 감지 범위 In
		RECT rt;
		if (IntersectRect(&rt, &_vNoteLeft[i].rc, &_beatRate) && !_vNoteLeft[i].isDestory)
		{
			_isBeat = true;

			if (_isSuccess)
			{
				_vNoteLeft[i].isDestory = true;
				_vNoteRight[i].isDestory = true;

				_beatCount++;
				_isBeat = false;
				_isSuccess = false;
			}
		}

		// 노트 삭제 조건
		if (_vNoteLeft[i].isDestory)
		{
			_vNoteLeft[i].speed = 0.f;
			_vNoteRight[i].speed = 0.f;

			_vNoteLeft[i].alpha -= 10;
			_vNoteRight[i].alpha -= 10;

			if (_vNoteLeft[i].alpha <= 0)
			{
				_vNoteLeft.erase(_vNoteLeft.begin() + i);
				_vNoteRight.erase(_vNoteRight.begin() + i);
			}
		}

		if (PtInRect(&_vNoteLeft[i].rc, _eraseLine))
		{
			_beatCount++;
			_isBeat = false;
			_vNoteLeft.erase(_vNoteLeft.begin() + i);
			_vNoteRight.erase(_vNoteRight.begin() + i);
		}
	}

	// 빗나감 상태가 true일 때 빗나감 객체 생성
	if (_isMissed)
	{
		createMissed();
		SOUNDMANAGER->play("missed_beat");
		_isMissed = false;
	}

	// 빗나감 객체 애니메이션
	moveMissed();
}

void Beat::render(HDC hdc)
{
	//노트 출력
	for (int i = 0; i < _vNoteLeft.size(); i++)
	{
		_vNoteLeft[i].img->frameAlphaRender(hdc, _vNoteLeft[i].x, _vNoteLeft[i].y, _vNoteLeft[i].frameX, _vNoteLeft[i].img->getFrameY(), _vNoteLeft[i].alpha);
		_vNoteRight[i].img->frameAlphaRender(hdc, _vNoteRight[i].x, _vNoteRight[i].y, _vNoteLeft[i].frameX, _vNoteLeft[i].img->getFrameY(), _vNoteRight[i].alpha);
	}

	// 심장 박동 출력
	_heartImg.img->frameRender(hdc, _heartImg.x, _heartImg.y);

	// 빗나감 출력
	for (auto iter = _vMissed.begin(); iter != _vMissed.end(); ++iter)
	{
		iter->img->alphaRender(hdc, iter->x, iter->y, iter->alpha);
	}
}

void Beat::createNote()
{
	for (int i = 0; i < 2; i++)
	{
		Note note;
		note.img = IMAGEMANAGER->findImage("beat_bar");
		note.y = WINSIZE_Y - 100;
		note.frameX = _noteFrameX;
		note.alpha = 50;
		note.isDestory = false;

		if (i == LEFT)
		{
			note.x = -50;
			note.speed = 5.0f;

			_vNoteLeft.push_back(note);
		}
		else
		{
			note.x = WINSIZE_X + 50 - note.img->getFrameWidth();
			note.speed = -5.0f;

			_vNoteRight.push_back(note);;
		}
	}
}

void Beat::createMissed()
{
	Missed missed;
	missed.img = IMAGEMANAGER->findImage("missed");
	missed.x = WINSIZE_X_HALF - _missedImg->getWidth() / 2;
	missed.y = WINSIZE_Y - 130;
	missed.alpha = 255;

	_vMissed.push_back(missed);
}

void Beat::moveMissed()
{
	for (auto iter = _vMissed.begin(); iter != _vMissed.end();)
	{
		iter->y -= 0.4f;
		iter->alpha -= 2;

		if (iter->alpha <= 0)
		{
			iter = _vMissed.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
