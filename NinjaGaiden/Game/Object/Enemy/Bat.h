#pragma once
#include "Enemy.h"
class Bat : public Enemy {
private:
	int leftMoving;
	int rightMoving;
	vector<int> movingLimit;
	vector<int> activeArea;
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	void init();
public:
	Bat();
	Bat(vector<int> movingLimit, vector<int> activeArea, int positionX, int positionY);
	~Bat();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void UpdateActiveArea(float t);
	void Dead();
	void SetState(ENEMY_STATE state);
};
