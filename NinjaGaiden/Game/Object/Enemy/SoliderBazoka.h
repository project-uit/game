#pragma once
#include "../../Framework/Object.h"
#include "../../Framework/Sprite.h"
#include "Bullet.h"
#include <map>

#define SHOOT_TIME_DELAY 1.4
#define SOLIDER_BAZOKA_VX 0
class SoliderBazoka :public Object {
private:
	vector<int> movingLimit;
	vector<int> activeArea;

	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	Bullet* bullet;
	float timerDelayShooting;
	bool isOnGround;
	void InitSpite();
	void HandleDirection();
	void HandleAttack(float t);
public:
	SoliderBazoka();
	SoliderBazoka(int posX, int posY, vector<int> movingLimit, vector<int> activeArea);
	~SoliderBazoka();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void Dead();
};