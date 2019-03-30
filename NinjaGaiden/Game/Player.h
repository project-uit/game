#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include <map>
#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

class Player : public Object
{
private:

	static Player* _instance;
	PLAYER_STATE state;
	PLAYER_STATE last_state;
	DIRECTION direction;
	map<PLAYER_STATE,Sprite*>* sprite;
public:
	Player();
	~Player();
	PLAYER_STATE GetState();
	void SetState(PLAYER_STATE value);
	DIRECTION GetDirection();
	void SetDirection(DIRECTION direction);
	void ResetAllSprites();
	bool GetStateActive();
	void SetLastState(PLAYER_STATE last_state);
	void Reset(float  x, float y);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void ResetSpriteState(PLAYER_STATE state);
	static Player* GetInstance() {
		if (_instance == NULL) _instance = new Player();
		return _instance;
	}
};

