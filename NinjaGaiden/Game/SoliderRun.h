#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Bullet.h"
#include <map>

#define SOLIDER_RUN_VX 100
class SoliderRun :public Object {
private:
	vector<int> movingLimit;
	vector<int> activeArea;

	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	float timerDelayShooting;
	bool isOnGround;
	void InitSpite();
	void HandleDirection();
	void HandleAttack(float t);
public:
	SoliderRun();
	SoliderRun(int posX, int posY, vector<int> movingLimit, vector<int> activeArea);
	~SoliderRun();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
};