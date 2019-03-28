#pragma once
#include "Game.h"
#include "World.h"
#include "Graphic.h"
#include "Player.h"

class KeyboardHandler : public InputDevice {
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};


class GameAction
{
private:
	static GameAction* _instance;
	KeyboardHandler* keyHandler;

public:
	GameAction(HINSTANCE hInstance, int nShowCmd);
	int GameRun();
	void Update(DWORD dt);
	void Render();
	static GameAction* GetInstance(HINSTANCE hInstance, int nShowCmd) {
		if (_instance == NULL) {
			_instance = new GameAction(hInstance, nShowCmd);
		}
		return _instance;
	}
};

