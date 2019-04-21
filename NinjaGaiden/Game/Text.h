#pragma once
#include "Game.h"
#include "Texture.h"
class Text
{
	static Text* __instance;
	ID3DXFont *font;
	Text();
public:
	~Text();
	static Text* GetInstance();
	void DrawString(std::string message, int x, int y, int width, int height, DWORD  color = D3DCOLOR_XRGB(255, 255, 255));
};