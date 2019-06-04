#pragma once
#include <d3dx9.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Constants.h"
#define GRAVITY 1400.0f
#define PLAYER_VELOCITY_X 175.0f
#define PLAYER_VELOCITY_Y 375.0f
#define NO_VELOCITY 0.0f

using namespace std;

class Object;

struct CollisionHandler
{

	Object* object;
	float collisionTime, nx, ny;
	CollisionHandler(float collisionTime, float nx, float ny, Object* obj = NULL) {
		this->collisionTime = collisionTime;
		this->nx = nx;
		this->ny = ny;
		this->object = obj;
	}

	static bool Compare(CollisionHandler* a, CollisionHandler *b) {
		return a->collisionTime < b->collisionTime;
	}
};

class Object
{
protected:
	int objectWidth;
	int objectHeight;
	D3DXVECTOR3 position;
	D3DXVECTOR3 lastPos;
	D3DXVECTOR3 veclocity;
	D3DXVECTOR2 positionColide;
	OBJECT_TYPE objectType;
	bool isActive;
	float deltaX;
	float deltaY;
	float deltaTime;
	int score;
public:
	Object();
	~Object();
	CollisionHandler* GetCollsionObjectsBySweptAABB(Object* obj);
	void CalcPotentialCollisions(vector<Object*> *objects, vector<CollisionHandler*> *coEvents);
	void FilterCollision(vector<CollisionHandler*> *coEvents, vector<CollisionHandler*> *coEventsResult,
		float &minTx, float &minTy, float &nx, float &ny);
	int GetScore();
	RECT GetBoundingBox();
	RECT GetRECTSprite();

	virtual void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	virtual void Render() = 0;
	virtual void HandleCollision(vector<Object*> *objects) = 0;
	virtual void ResetState();
	virtual void Dead();

	D3DXVECTOR3 GetVeclocity();
	void SetVeclocity(float vx, float vy);
	void SetVx(float vx);
	void SetVy(float vy);
	//Tọa độ dùng để render khi có Camera
	D3DXVECTOR3 GetTransformObjectPositionByCamera();
	D3DXVECTOR3 GetPosition();
	void SetPosition(float x, float y);
	void PlusPosition(float x, float y);
	void updateBoundingBox(RECT rect);
	void SetBoundingBox(int width, int height);
	void SetObjectBoudingBox(int &width, int &height);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetObjectType(OBJECT_TYPE objectType);
	OBJECT_TYPE GetObjectType();
	void SetLastPos(float x, float y);
	void SetLastPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetLastPos();
	DIRECTION GetObjectDirection();
	void SetActive(bool active);
	bool GetActive();
};

