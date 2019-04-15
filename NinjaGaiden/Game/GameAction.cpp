#include "GameAction.h"

GameAction *GameAction::_instance = NULL;

GameAction::GameAction(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_SCREEN_320_240);
	//SetWindowPos(graphic->GetHWnd(), 0, 0, 0, graphic->GetWidth()*2, graphic->GetHeight()*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Game *game = Game::GetInstance();
	game->Init(graphic->GetHWnd());

	this->keyHandler = new KeyboardHandler();
	game->InitKeyboard(this->keyHandler);

	Camera::SetInstance(graphic->GetWidth(), graphic->GetHeight(), 0, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
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
		else {
			Sleep(tickPerFrame - deltaTime);
		}
	}

	return 1;
}

void GameAction::Update(DWORD dt)
{
	World::GetInstance()->Update( (float) dt);
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition().x, Player::GetInstance()->GetPosition().y, 2048, 320);
}

void GameAction::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();

	if (d3ddv->BeginScene()) {
		d3ddv->ColorFill(Game::GetInstance()->GetBackBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));
		Game::GetInstance()->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
		
		World::GetInstance()->Render();
		//Camera::GetInstance()->SetTransForm(Game::GetInstance()->GetDirect3DDevice());
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
	if (Player::GetInstance()->GetState() != PLAYER_STATE::DIE) {
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT)) {
			Player::GetInstance()->SetVeclocity(PLAYER_VELOCITY_X, NO_VELOCITY);
			Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
			Player::GetInstance()->SetState(PLAYER_STATE::RUN);
		}

		if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) {
			Player::GetInstance()->SetVeclocity(-PLAYER_VELOCITY_X, NO_VELOCITY);
			Player::GetInstance()->SetDirection(DIRECTION::LEFT);
			Player::GetInstance()->SetState(PLAYER_STATE::RUN);
		}

		if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) {
			Player::GetInstance()->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
			Player::GetInstance()->SetState(PLAYER_STATE::SIT);
		}

		if (Player::GetInstance()->GetLastState() == PLAYER_STATE::SIT) {
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::SIT_ATK);
			}
		}

		if (KeyCode == DIK_UP) {
			Player::GetInstance()->SetVy(-PLAYER_VELOCITY_Y);
		}

		if (Player::GetInstance()->GetLastState() == PLAYER_STATE::STAND) {
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::STAND_ATK);
			}
			if (KeyCode == DIK_X) {
				/*Player::GetInstance()->SetState(PLAYER_STATE::JUMP);
				Player::GetInstance()->SetVy(-PLAYER_VELOCITY_Y);*/
			}
		}
	} 
}

void KeyboardHandler::OnKeyUp(int KeyCode)
{
	//DebugOut((wchar_t *)L"[GameAction.cpp][KEYBOARD] KeyUp: %d\n", KeyCode);
	if (Player::GetInstance()->GetState() != PLAYER_STATE::DIE) {
		if (KeyCode == DIK_RIGHT) {
			Player::GetInstance()->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
			Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
			Player::GetInstance()->SetState(PLAYER_STATE::STAND);
		}

		if (KeyCode == DIK_LEFT) {
			Player::GetInstance()->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
			Player::GetInstance()->SetDirection(DIRECTION::LEFT);
			Player::GetInstance()->SetState(PLAYER_STATE::STAND);
		}

		if (KeyCode == DIK_DOWN) {
			Player::GetInstance()->SetState(PLAYER_STATE::STAND);
		}

		if (Player::GetInstance()->GetState() == PLAYER_STATE::SIT_ATK) {
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::SIT);
			}
		}

		if (Player::GetInstance()->GetLastState() == PLAYER_STATE::STAND_ATK) {
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::STAND);
			}
		}
	}
}