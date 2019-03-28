#include "GameAction.h"
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	GameAction* game = GameAction::GetInstance(hInstance, nShowCmd);
	game->GameRun();
	return 0;
}