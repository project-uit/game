#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include <map>
#include "Item.h"
#include "Katana.h"
#include "SmallShuriken.h"
#include "Food.h"
#include "CircleFire.h"
#include "Rock.h"
#include "Brick.h"
#include "Ladder.h"
#define CIRCLE_FIRE_NUMBER 3
class Player : public Object
{
private:

	static Player* _instance;
	PLAYER_STATE state;
	PLAYER_STATE last_state;
	DIRECTION direction;
	map<PLAYER_STATE,Sprite*>* sprite;
	Food* food;
	bool isOnGround;
	bool isWounded;
	bool isOnLadder;
	bool isOnRock;
	bool isJumpClimb;
	bool isClimbMoving;
	DIRECTION directionClimb;
	int hp;
	float acceleratorX, acceleratorY;
	Katana* katana;
	Weapon* weapon;
	Ladder* currentLadder;
	Rock* currentRock;
	float time;
	int count;
	int itemPoint;
	int lifePoint;
	float borderBot;
	float freezeTime;
	int alphaEndPoint;
	bool endStage;
public:
	Player();
	~Player();
	PLAYER_STATE GetState();
	void SetState(PLAYER_STATE value);
	DIRECTION GetDirection();
	DIRECTION GetDirectionClimb();
	void SetDirection(DIRECTION direction);
	void ResetAllSprites();
	bool GetStateActive();
	PLAYER_STATE GetLastState();
	void IntersectPlayer(Object* object, DIRECTION direction);
	void SetLastState(PLAYER_STATE last_state);
	void SetOnGround(bool isOnGround);
	bool GetOnGround();
	bool GetWounded();
	bool Wounded(float nx, float ny, Object* object, DIRECTION direction);
	Sprite* GetCurrentSprite();
	void Reset(float  x, float y);
	void SetAcceleratorX(float x);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void ResetSpriteState(PLAYER_STATE state);
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void UseWeapon();
	int GetLifePoint();
	int GetItemPoint();
	int GetHp();
	void SetHp(int hp);
	float GetAcceleratorX();
	float GetBorderBot();
	string GetScoreString();
	Katana* GetKatana();
	Weapon* GetWeapon();
	Food* GetFood();
	void AddScore(int score);
	void KillEnemy(Object* object);
	bool GetIsJumpClimb();
	void JumpClimb(int KeyCode);
	void SetClimbRock(float nx, float ny, Rock* rock);
	void SetClimbMoving(bool flag);
	void DigestFood(Food* food, Sprite* sprite);
	float GetFreezeTime();
	void MinusFreezeTime();
	bool isFreezeTime();
	int GetAlphaEndPoint();
	void SetAlphaEndPoint(int alpha);
	void MinusAlphaEndPoint();
	void Restart(float x, float y);
	static Player* GetInstance() {
		if (_instance == NULL) _instance = new Player();
		return _instance;
	}
};

