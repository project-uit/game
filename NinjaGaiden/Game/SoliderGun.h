#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Bullet.h"
#include <map>

#define MAX_NUMBER_OF_BULLET 3
#define SHOOT_TIME_DELAY 1.4
#define SOLIDERGUN_VX 30.0f
class SoliderGun :public Object {
private:
	vector<int> movingLimit;
	vector<int> activeArea;

	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;

	Bullet* bullet[MAX_NUMBER_OF_BULLET];
	int countShoot;
	bool isOnGround;
	DIRECTION direction;
	float timerDelayShooting;
	
	void InitSpite();
	void HandleDirection();
	void HandleAttack(float t);
public:
	SoliderGun();
	SoliderGun(int posX, int posY, vector<int> movingLimit, vector<int> activeArea);
	~SoliderGun();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void GotoStateFollow();
};