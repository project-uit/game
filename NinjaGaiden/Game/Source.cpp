#include "Framework/GameAction.h"
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	GameAction* game = GameAction::GetInstance(hInstance, nShowCmd);
	Graphic *graphic = Graphic::GetInstance(NULL, NULL, L"", 1);
	SetWindowPos(graphic->GetHWnd(), 0, 0, 0, graphic->GetWidth() * 2.5, graphic->GetHeight() * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	game->GameRun();
	return 0;
}