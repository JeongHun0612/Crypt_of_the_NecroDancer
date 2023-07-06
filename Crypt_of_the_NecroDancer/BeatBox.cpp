#include "Stdafx.h"
#include "BeatBox.h"

HRESULT BeatBox::init(void)
{
	_beatBoxImg = IMAGEMANAGER->findImage("beat_box");
	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - _beatBoxImg->getFrameHeight() / 2 - 20, 150, 100);

	_count = 0.0f;

	return S_OK;
}

void BeatBox::release(void)
{
}

void BeatBox::update(void)
{
	// ��Ʈ �ڽ� �̹��� ������ ����
	_count += TIMEMANAGER->getElapsedTime();

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
	// ��Ʈ �����
	for (auto iter = _vBeatBar.begin(); iter != _vBeatBar.end(); ++iter)
	{
		DrawRectMake(getMemDC(), iter->rc);
		iter->img->render(getMemDC(), iter->pos.x, iter->pos.y);
	}

	// ��Ʈ �ڽ� ����
	DrawRectMake(getMemDC(), _rc);

	// ��Ʈ �ڽ�
	_beatBoxImg->frameRender(getMemDC(),
		WINSIZE_X / 2 - _beatBoxImg->getFrameWidth() / 2,
		WINSIZE_Y - _beatBoxImg->getFrameHeight() - 20,
		_beatBoxImg->getFrameX(),
		_beatBoxImg->getFrameY());
}

void BeatBox::crateBeatBar()
{
	static float count = 0.0f;

	count += TIMEMANAGER->getElapsedTime();

	if (count >= 1.0f)
	{
		for (int i = 0; i < 2; i++)
		{
			BeatBar beatBar;

			beatBar.img = IMAGEMANAGER->findImage("beat_bar1");

			beatBar.pos.x = (i % 2 == 0) ? -50 : WINSIZE_X + 50;
			beatBar.pos.y = WINSIZE_Y - 100;

			beatBar.rc = { 0 ,0, 0, 0 };

			beatBar.direction = (i % 2 == 0) ? 0 : 1;	// 0 : LEFT  1 : RIGHT
			beatBar.speed = 5.0f;

			_vBeatBar.push_back(beatBar);
		}

		count = 0.0f;
	}
}

void BeatBox::moveBeatBar()
{
	for (auto iter = _vBeatBar.begin(); iter != _vBeatBar.end();)
	{
		if (iter->direction == 0)
		{
			iter->pos.x += iter->speed;
		}
		else
		{
			iter->pos.x -= iter->speed;
		}

		// �浹ü ��ġ ������
		iter->rc = RectMake(iter->pos.x, iter->pos.y, 12, 64);

		// ��Ʈ ����� ���� (��� �������� ��)
		if (iter->rc.left == WINSIZE_X / 2)
		{
			iter = _vBeatBar.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
