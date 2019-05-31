#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>

#define WITCH_SWORD_VY 300.0f
class WitchSword :public Object {
private:
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	D3DXVECTOR3 witchPosition;
	int countThrow;
public:
	WitchSword(int positionX, int positionY, DIRECTION direction);
	~WitchSword();
	void Update(float t, vector<Object*>* objects);
	void UpdateWitchPosition(D3DXVECTOR3 witchPosition);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void Fly(int vX, DIRECTION direction);
	void Dead();
	void SetState(ENEMY_STATE state);
};