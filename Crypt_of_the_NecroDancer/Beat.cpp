#include "Stdafx.h"
#include "Beat.h"
#include "FileManager.h"

HRESULT Beat::init(void)
{
	// 노트 정보 불러오기 (stage 1-1)
	FileManager::loadBeatFile("stage1-1.txt", _qNoteData);

	// 심장 박동 초기화
	_heartRate.img = IMAGEMANAGER->findImage("beat_heart");
	_heartRate.x = WINSIZE_X_HALF - _heartRate.img->getFrameWidth() / 2;
	_heartRate.y = WINSIZE_Y - 130;
	_heartRate.rc = RectMakeCenter(_heartRate.x + _heartRate.img->getFrameWidth() / 2, _heartRate.y + _heartRate.img->getFrameHeight() / 2, 150, 100);
	_heartRate.frameX = 0;
	_heartRate.frameY = 0;
	_heartRate.frameCount = 0.0f;

	_eraseLine = { WINSIZE_X_HALF, WINSIZE_Y - 80 };

	// 빗나감 이미지 초기화
	_missedImg = IMAGEMANAGER->findImage("missed");
	_missedImg->setX(WINSIZE_X_HALF - _missedImg->getWidth() / 2);
	_missedImg->setY(WINSIZE_Y - 130);
	_missedAlpha = 255;

	_noteCycle = _qNoteData.front();
	_qNoteData.pop();

	_isBeat = false;
	_isMusic = true;
	_isMissed = false;
	_isSuccess = false;

	return S_OK;
}

void Beat::release(void)
{

}

void Beat::update(void)
{
	// 심장 박동 애니메이션
	_heartRate.frameCount += TIMEMANAGER->getDeltaTime();

	if (_heartRate.frameCount >= 0.276f)
	{
		if (_heartRate.frameX == _heartRate.img->getMaxFrameX())
		{
			_heartRate.frameX = 0;
		}
		else
		{
			_heartRate.frameX++;
		}

		_heartRate.img->setFrameX(_heartRate.frameX);

		_heartRate.frameCount = 0;
	}


	// 노트 생성
	unsigned int soundPos = SOUNDMANAGER->getPosition("stage1-1");

	//static int test = 0;
	//test += 10;

	if (_noteCycle <= soundPos && _isMusic)
	{
		createNote();

		_noteCycle = _qNoteData.front();
		_qNoteData.pop();

		// 노트가 비었을 때 음악 종료
		if (_qNoteData.empty())
		{
			_isMusic = false;
		}
	}

	for (int i = 0; i < _vNoteLeft.size(); i++)
	{
		// 노트 이동
		_vNoteLeft[i].x += _vNoteLeft[i].speed;
		_vNoteLeft[i].rc = RectMake(_vNoteLeft[i].x, _vNoteLeft[i].y, _vNoteLeft[i].img->getWidth(), _vNoteLeft[i].img->getHeight());

		_vNoteRight[i].x += _vNoteRight[i].speed;
		_vNoteRight[i].rc = RectMake(_vNoteRight[i].x, _vNoteRight[i].y, _vNoteRight[i].img->getWidth(), _vNoteRight[i].img->getHeight());

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
		if (IntersectRect(&rt, &_vNoteLeft[i].rc, &_heartRate.rc) && !_vNoteLeft[i].isDestory)
		{
			_isBeat = true;

			if (_isSuccess)
			{
				_vNoteLeft[i].isDestory = true;
				_vNoteRight[i].isDestory = true;

				_isSuccess = false;
				_isBeat = false;
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
			_vNoteLeft.erase(_vNoteLeft.begin() + i);
			_vNoteRight.erase(_vNoteRight.begin() + i);
		}
	}


	// 빗나감 상태가 true일 때 빗나감 객체 생성
	if (_isMissed)
	{
		_isMissed = false;

		createMissed();
	}

	// 빗나감 객체 애니메이션
	moveMissed();
}

void Beat::render(HDC hdc)
{
	//노트 출력
	for (int i = 0; i < _vNoteLeft.size(); i++)
	{
		_vNoteLeft[i].img->alphaRender(hdc, _vNoteLeft[i].x, _vNoteLeft[i].y, _vNoteLeft[i].alpha);
		_vNoteRight[i].img->alphaRender(hdc, _vNoteRight[i].x, _vNoteRight[i].y, _vNoteRight[i].alpha);
	}

	// 심장 박동 출력
	_heartRate.img->frameRender(hdc, _heartRate.x, _heartRate.y);

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		DrawRectMake(hdc, _heartRate.rc);
	}

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
		note.img = IMAGEMANAGER->findImage("beat_bar1");
		note.y = WINSIZE_Y - 100;
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
			note.x = WINSIZE_X + 50;
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
