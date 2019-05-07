#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include <map>
#include "Item.h"
#include "Katana.h"

class Player : public Object
{
private:

	static Player* _instance;
	PLAYER_STATE state;
	PLAYER_STATE last_state;
	DIRECTION direction;
	map<PLAYER_STATE,Sprite*>* sprite;
	bool isOnGround;
	bool isOnLadder;
	bool isWounded;
	int hp;
	float acceleratorX, acceleratorY;
	Katana* katana;
	float time;
	int count;
	float y;
public:
	Player();
	~Player();
	PLAYER_STATE GetState();
	void SetState(PLAYER_STATE value);
	DIRECTION GetDirection();
	void SetDirection(DIRECTION direction);
	void ResetAllSprites();
	bool GetStateActive();
	PLAYER_STATE GetLastState();
	void SetLastState(PLAYER_STATE last_state);
	void SetOnGround(bool isOnGround);
	bool GetOnGround();
	bool GetWounded();
	Sprite* GetCurrentSprite();
	void Reset(float  x, float y);
	void SetAcceleratorX(float x);
	void SetAcceleratorY(float y);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void ResetSpriteState(PLAYER_STATE state);
	void HandleCollision(vector<Object*> *object);
	Katana* GetKatana();
	static Player* GetInstance() {
		if (_instance == NULL) _instance = new Player();
		return _instance;
	}
};

