#include "GameAction.h"
#include "GameTime.h"
#define MAX_FRAME_RATE 170
GameAction *GameAction::_instance = NULL;

GameAction::GameAction(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_SCREEN_320_240);
	Game *game = Game::GetInstance();
	game->Init(graphic->GetHWnd());
	this->keyHandler = new KeyboardHandler();
	game->InitKeyboard(this->keyHandler);
	World *world = World::GetInstance();
	world->LoadResource();
	GameTime::GetInstance();
}

int GameAction::GameRun()
{
	MSG msg;
	int done = 0;

	DWORD frameStart = GetTickCount();
	float tickPerFrame = 1.0f / MAX_FRAME_RATE, delta = 0;

	while (!done) {
		GameTime::GetInstance()->StartCounter();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		delta += GameTime::GetInstance()->GetCouter();
		//DWORD now = GetTickCount();	
		//DWORD deltaTime = now - frameStart;
		if (delta >= tickPerFrame)
		{
			//frameStart = now;
			Game::GetInstance()->ProcessKeyboard();
			this->Update(delta);
			this->Render();
			delta = 0;
		}
		else {
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}
	return 1;
}

void GameAction::Update(float dt)
{
	World::GetInstance()->Update(dt);
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
	/*DebugOut((wchar_t *)L"[GameAction.cpp][KEYBOARD] KeyDown: %d\n", KeyCode);*/
	if (Player::GetInstance()->GetState() != PLAYER_STATE::DIE) {

		if (Player::GetInstance()->GetOnGround()) {
			if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) {
				Player::GetInstance()->SetVx(-PLAYER_VELOCITY_X);
				Player::GetInstance()->SetAcceleratorX(-25.0f);
				Player::GetInstance()->SetDirection(DIRECTION::LEFT);
				Player::GetInstance()->SetState(PLAYER_STATE::RUN);
			}
			if (Game::GetInstance()->IsKeyDown(DIK_RIGHT)) {
				Player::GetInstance()->SetAcceleratorX(25.0f);
				Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
				Player::GetInstance()->SetState(PLAYER_STATE::RUN);
			}
		}

		if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) {
			if (Player::GetInstance()->GetState() == PLAYER_STATE::STAND) {
				Player::GetInstance()->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				Player::GetInstance()->SetState(PLAYER_STATE::SIT);
			}
		}

		if (Player::GetInstance()->GetLastState() == PLAYER_STATE::SIT) {
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::SIT_ATK);
			}
		}

		if (Player::GetInstance()->GetState() == PLAYER_STATE::STAND) {
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::STAND_ATK);
			}
			if (KeyCode == DIK_X) {
				Player::GetInstance()->SetState(PLAYER_STATE::JUMP);
				Player::GetInstance()->SetVy(-PLAYER_VELOCITY_Y);
				Player::GetInstance()->SetOnGround(false);
			
			}
		}

		if (Player::GetInstance()->GetState() == PLAYER_STATE::RUN) {
			if (KeyCode == DIK_X) {
				Player::GetInstance()->SetState(PLAYER_STATE::JUMP);
				Player::GetInstance()->SetVy(-PLAYER_VELOCITY_Y);				
				Player::GetInstance()->SetOnGround(false);
			}
		}

		if (Player::GetInstance()->GetState() == PLAYER_STATE::JUMP) {
			if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) {
				Player::GetInstance()->SetAcceleratorX(-20.0f);
				Player::GetInstance()->SetDirection(DIRECTION::LEFT);
			}
			if (Game::GetInstance()->IsKeyDown(DIK_RIGHT)) {
				Player::GetInstance()->SetAcceleratorX(20.0f);
				Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
			}
			if (KeyCode == DIK_Z) {
				Player::GetInstance()->SetState(PLAYER_STATE::STAND_ATK);
				Player::GetInstance()->SetAcceleratorX(0.0f);
				Player::GetInstance()->SetVx(0.0f);
			}
		}
	}
}

void KeyboardHandler::OnKeyUp(int KeyCode)
{
	
	if (Player::GetInstance()->GetState() != PLAYER_STATE::DIE) {
		if (KeyCode == DIK_RIGHT) {
			if (Player::GetInstance()->GetState() == PLAYER_STATE::RUN) {
				Player::GetInstance()->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				Player::GetInstance()->SetAcceleratorX(0.0f);
				Player::GetInstance()->SetDirection(DIRECTION::RIGHT);
				Player::GetInstance()->SetState(PLAYER_STATE::STAND);
			}
		}

		if (KeyCode == DIK_LEFT) {
			if (Player::GetInstance()->GetState() == PLAYER_STATE::RUN) {
				Player::GetInstance()->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				Player::GetInstance()->SetAcceleratorX(0.0f);
				Player::GetInstance()->SetDirection(DIRECTION::LEFT);
				Player::GetInstance()->SetState(PLAYER_STATE::STAND);
			}
		}

		if (Player::GetInstance()->GetState() == PLAYER_STATE::SIT) {
			if (KeyCode == DIK_DOWN) {
				Player::GetInstance()->SetState(PLAYER_STATE::STAND);
			}
		}
	}
}