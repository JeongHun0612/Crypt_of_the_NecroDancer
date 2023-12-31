#pragma once

struct Vec2
{
	int x;
	int y;
};

struct Vec2_F
{
	float x;
	float y;
};

struct FrameImage
{
	GImage* img;

	float x, y;
	int startFrameX;
	int startFrameY;
	int frameX;
	int frameY;
	int maxFrameX;
	float frameCount;
};

struct AlphaImage
{
	GImage* img;
	Vec2 posIdx;
	Vec2_F pos;
	int alpha;
};

