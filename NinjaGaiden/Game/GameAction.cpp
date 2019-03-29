#include "GameAction.h"

GameAction *GameAction::_instance = NULL;

GameAction::GameAction(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_SCREEN_640_480);
	/*SetWindowPos(graphic->GetHWnd(), 0, 0, 0, graphic->GetWidth(), graphic->GetHeight(), SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);*/

	Game *game = Game::GetInstance();
	game->Init(graphic->GetHWnd());

	this->keyHandler = new KeyboardHandler();
	game->InitKeyboard(this->keyHandler);


	World *world = World::GetInstance();
	world->LoadResource();
}

// Các xử lý update và hiển thị nhân vật
int GameAction::GameRun()
{
	MSG msg;
	int done = 0;

	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		DWORD deltaTime = now - frameStart;

		if (deltaTime >= tickPerFrame)
		{
			frameStart = now;

			Game::GetInstance()->ProcessKeyboard();

			this->Update(deltaTime);
			this->Render();
		}
		else
			Sleep(tickPerFrame - deltaTime);
	}

	return 1;
}

void GameAction::Update(DWORD dt)
{
	World::GetInstance()->Update( (float) dt);
}

void GameAction::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();

	if (d3ddv->BeginScene()) {
		d3ddv->ColorFill(Game::GetInstance()->GetBackBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));
		Game::GetInstance()->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		World::GetInstance()->Render();

		Game::GetInstance()->GetSpriteHandler()->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void KeyboardHandler::KeyState(BYTE * states)
{

}

void KeyboardHandler::OnKeyDown(int KeyCode)
{
	DebugOut((wchar_t *)L"[KEYBOARD] KeyDown: %d\n",KeyCode);
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT)) {
		Player::GetInstance()->SetVeclocity(0.2f, 0);
		Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
		Player::GetInstance()->SetState(PLAYER_STATE::RUN);
	}

	if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) {
		Player::GetInstance()->SetVeclocity(-0.2f, 0);
		Player::GetInstance()->SetDirection(DIRECTION::LEFT);
		Player::GetInstance()->SetState(PLAYER_STATE::RUN);
	}

	if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) {
		Player::GetInstance()->SetVeclocity(0, 0);
		Player::GetInstance()->SetState(PLAYER_STATE::SIT);
	}
}

void KeyboardHandler::OnKeyUp(int KeyCode)
{
	DebugOut((wchar_t *)L"[KEYBOARD] KeyUp: %d\n", KeyCode);
	if (KeyCode == DIK_RIGHT) {
		Player::GetInstance()->SetVeclocity(0, 0);
		Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
		Player::GetInstance()->SetState(PLAYER_STATE::STAND);
	}

	if (KeyCode == DIK_LEFT) {
		Player::GetInstance()->SetVeclocity(0, 0);
		Player::GetInstance()->SetDirection(DIRECTION::LEFT);
		Player::GetInstance()->SetState(PLAYER_STATE::STAND);
	}

	if (KeyCode == DIK_DOWN) {
		Player::GetInstance()->SetState(PLAYER_STATE::STAND);
	}
}