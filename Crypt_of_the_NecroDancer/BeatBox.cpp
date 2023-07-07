#include "Stdafx.h"
#include "BeatBox.h"

HRESULT BeatBox::init(void)
{
	// ���� �̹���
	_beatBoxImg = IMAGEMANAGER->findImage("beat_heart");
	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 70, 150, 100);

	// ������ �̹���
	_missed.img = IMAGEMANAGER->findImage("missed");
	_missed.x = WINSIZE_X / 2 - _missed.img->getWidth() / 2;
	_missed.y = WINSIZE_Y - 90;
	_missed.alpha = 255;

	_count = 0.0f;
	_isMissed = false;

	return S_OK;
}

void BeatBox::release(void)
{
}

void BeatBox::update(void)
{
	// ��Ʈ �ڽ� �̹��� ������ ����
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.5f)
	{
		if (_beatBoxImg->getFrameX() == 0)
		{
			_beatBoxImg->setFrameX(1);
		}
		else
		{
			_beatBoxImg->setFrameX(0);
		}

		_count = 0.0f;
	}


	// ��Ʈ ����� ����
	crateBeatBar();

	// ��Ʈ ����� ��ġ ����
	moveBeatBar();

}

void BeatBox::render(void)
{
	// ��Ʈ
	for (auto iter = _vBeatBar.begin(); iter != _vBeatBar.end(); ++iter)
	{
		DrawRectMake(getMemDC(), iter->rc);
		iter->img->render(getMemDC(), iter->x, iter->y);
	}

	// ��Ʈ �ڽ� ����
	DrawRectMake(getMemDC(), _rc);

	// ��Ʈ �ڽ�
	_beatBoxImg->frameRender(getMemDC(),
		WINSIZE_X / 2 - _beatBoxImg->getFrameWidth() / 2,
		WINSIZE_Y - _beatBoxImg->getFrameHeight() - 20,
		_beatBoxImg->getFrameX(),
		_beatBoxImg->getFrameY());


	// ������ ó��
	_missed.img->alphaRender(getMemDC(), _missed.x, _missed.y, _missed.alpha);
}

void BeatBox::crateBeatBar()
{
	static float count = 0.0f;

	count += TIMEMANAGER->getDeltaTime();

	if (count >= 1.0f)
	{
		BeatBar beatBar[2];

		beatBar[LEFT].img = IMAGEMANAGER->findImage("beat_bar1");
		beatBar[LEFT].x = -50;
		beatBar[LEFT].y = WINSIZE_Y - 100;
		beatBar[LEFT].speed = 5.0f;

		beatBar[RIGHT].img = IMAGEMANAGER->findImage("beat_bar1");
		beatBar[RIGHT].x = WINSIZE_X + 50;
		beatBar[RIGHT].y = WINSIZE_Y - 100;
		beatBar[RIGHT].speed = -5.0f;

		_vBeatBar.push_back(beatBar);

		count = 0.0f;
	}
}

void BeatBox::moveBeatBar()
{
	for (auto iter = _vBeatBar.begin(); iter != _vBeatBar.end();)
	{
		// ��Ʈ �̵�
		for (int i = 0; i < 2; i++)
		{
			iter[i]->x += iter[i]->speed;
			iter[i]->rc = RectMake(iter[i]->x, iter[i]->y, 12, 64);
		}

		// ��� ���� ����
		if (iter[LEFT]->rc.right == iter[RIGHT]->rc.left)
		{
			iter = _vBeatBar.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
