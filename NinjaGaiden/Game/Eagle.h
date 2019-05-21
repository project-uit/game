#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
#define MAX_DISTANCE_PLAYER 70
#define AVE_DISTANCE_PLAYER 50
#define MIN_DISTANCE_PLAYER 5
class Eagle : public Object {
private:
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	vector<int> activeArea;
	vector<int> number;
	bool firstFly;
	int finishFly;
	int top, bottom;
	float destination;
	float time;
	float left, right; 
	void init();
public:
	Eagle();
	Eagle(vector<int> activeArea, int positionX, int positionY);
	~Eagle();
	void UpdatteActiveArea(float t);
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void FollowPlayer(float t);
	void ChangeDistance(float vx, float vy);
};