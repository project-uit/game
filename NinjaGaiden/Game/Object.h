#pragma once
#include <d3dx9.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Constants.h"
#define GRAVITY 0.00009f
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
	Object* nextObj;
	Object* preObj;
	float deltaX;
	float deltaY;
	float deltaTime;
	
public:
	Object();
	~Object();

	bool checkAABB(Object* obj);

	void SweptAABB(Object* obj, float deltaX, float deltaY, float &collisionTime, float &nx, float& ny);
	CollisionHandler* GetCollsionObjectsBySweptAABB(Object* obj);
	void CalcPotentialCollisions(vector<Object*> *objects, vector<CollisionHandler*> *coEvents);
	void FilterCollision(vector<CollisionHandler*> *coEvents, vector<CollisionHandler*> *coEventsResult, float &minTx, float &minTy, float &nx, float &ny);

	RECT GetBoundingBox();
	RECT GetRECTSprite();

	virtual void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	virtual void Render() = 0;
	virtual void HandleCollision(vector<Object*> *objects) = 0;

	D3DXVECTOR3 GetVeclocity() { return this->veclocity; }
	void SetVeclocity(float vx, float vy) { this->veclocity.x = vx; this->veclocity.y = vy; }
	void SetVx(float vx) { 
		this->veclocity.x = vx; 
	}
	void SetVy(float vy) { 
		this->veclocity.y = vy; 
	}
	//Tọa độ dùng để render
	D3DXVECTOR3 GetTransformObjectPositionByCamera();

	D3DXVECTOR3 GetPosition() { return this->position; }
	void SetPosition(float x, float y) { 
		this->position.x = x; 
		this->position.y = y; 
	}
	void PlusPosition(float x, float y) { 
		this->position.x += x; 
		this->position.y += y; 
	}

	void updateBoundingBox(RECT rect) {
		positionColide.x = rect.left;
		positionColide.y = rect.top;
		SetBoundingBox(rect.right - rect.left, rect.bottom - rect.top);
	}

	void SetBoundingBox(int width, int height) { 
		this->objectWidth = width; 
		this->objectHeight = height; 
	}

	void SetObjectBoudingBox(int &width, int &height) { 
		width = this->objectWidth; 
		height = this->objectHeight; 
	}

	void SetPositionX(float x) {
		this->position.x += x;
	}

	void SetPositionY(float y) {
		this->position.y += y;
	}

	void SetObjectType(OBJECT_TYPE objectType) { this->objectType = objectType; }
	OBJECT_TYPE GetObjectType() { return this->objectType; }

	void SetNextObj(Object* obj) { this->nextObj = obj; }
	Object* GetNextObj() { return this->nextObj; }

	void SetPreObj(Object* obj) { this->preObj = obj; }
	Object* GetPreObj() { return this->preObj; }

	void SetLastPos(float x, float y) { this->lastPos.x = x; this->lastPos.y = y; }
	void SetLastPos(D3DXVECTOR3 pos) { this->lastPos.x = pos.x; this->lastPos.y = pos.y; }
	D3DXVECTOR3 GetLastPos() { return this->lastPos; }
};

