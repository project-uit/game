#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>

#define BULLET_VX 180.0f
#define BULLET_DELAY_TIME 0.1f
class Bullet :public Object {
private:
	BULLET_TYPE type;
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	D3DXVECTOR3 soliderPosition;
public:
	Bullet(int positionX, int positionY, BULLET_TYPE type, DIRECTION direction);
	~Bullet();
	void Update(float t, vector<Object*>* objects);
	void UpdateSoliderPosition(D3DXVECTOR3 witchPosition);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void Fly(DIRECTION direction);
	void Dead();
	void SetState(ENEMY_STATE state);
};