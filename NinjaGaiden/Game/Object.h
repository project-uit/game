#pragma once
#include <d3dx9.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Constants.h"
using namespace std;

class Object;

class CollisionHandler
{
private:
	Object* obj;
	float collisionTime, nx, ny;
public:
	CollisionHandler(float collisionTime, float nx, float ny, Object* obj = NULL);
	~CollisionHandler();

	static bool Compare(CollisionHandler* a, CollisionHandler *b) {
		return a->collisionTime < b->collisionTime;
	}

	float GetCollisionTime() {
		return this->collisionTime;
	}

	float GetNx() {
		return this->nx;
	}

	float GetNy() {
		return this->ny;
	}
};

class Object
{
protected:
	int objectWidth;
	int objectHeight;
	D3DXVECTOR3 position;  // Vị trí hiện tại của object
	D3DXVECTOR3 lastPos;	// Vị trí trước đó của object
	D3DXVECTOR3 veclocity;  // Vận tốc của Object
	OBJECT_TYPE objectType;
	bool isActive;

	// 2 trường này phục vụ cho Grid
	Object* nextObj;
	Object* preObj;

	// Cái này dùng để hỗ trợ cập nhật vị trí của object
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

	virtual void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	virtual void Render() = 0;

	D3DXVECTOR3 GetVeclocity() { return this->veclocity; }
	void SetVeclocity(float vx, float vy) { this->veclocity.x = vx; this->veclocity.y = vy; }
	void SetVx(float vx) { this->veclocity.x = vx; }
	void SetVy(float vy) { this->veclocity.y = vy; }

	D3DXVECTOR3 GetPosition() { return this->position; }
	void SetPosition(float x, float y) { this->position.x = x; this->position.y = y; }
	void PlusPosition(float x, float y) { this->position.x += x; this->position.y += y; }

	void SetBoundingBox(int width, int height) { this->objectWidth = width; this->objectHeight = height; }
	void GetObjectBoudingBox(int &width, int &height) { width = this->objectWidth; height = this->objectHeight; }

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

