#include "Text.h"
Text* Text::__instance = NULL;
Text::Text() {
	font = NULL;
	D3DXCreateFont(Game::GetInstance()->GetDirect3DDevice(), 15, 0, 600, 1, 
		false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE,L"Arial", &font);
}

Text::~Text() {
	if (font != NULL) {
		delete font;
	}
}

Text* Text::GetInstance() {
	if (__instance == NULL) {
		__instance = new Text();
	}
	return __instance;
}

void Text::DrawString(std::string message, int x, int y, int width, int height, DWORD  color) {
	if (font)
	{
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_LEFT, color);
	}
}