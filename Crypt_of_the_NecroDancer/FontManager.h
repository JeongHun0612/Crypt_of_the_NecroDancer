#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{
private:

public:
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fonsSize, int fontWidth, 
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fonsSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fonsSize, int fontWidth, 
		LPCWSTR* printStringArr, int length, COLORREF color);

	FontManager() {}
	~FontManager() {}
};

