#include "Text.h"
#include "Debug.h"
Text* Text::__instance = NULL;
Text::Text() {
	font = NULL;
	//if (AddFontResourceEx(L"sprite\\font\\NinjaGaiden.ttf", FR_PRIVATE, 0)) {
	//	DebugOut((wchar_t *)L"Loading Custom Font Successfully\n");
	//}
	D3DXCreateFont(Game::GetInstance()->GetDirect3DDevice(), 12, 0, 600, 1, 
		false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Terminal", &font);
}

Text::~Text() {
	if (font != NULL) {
		font->Release();
		font = NULL;
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