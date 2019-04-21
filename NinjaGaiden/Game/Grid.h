#pragma once
#include "Object.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define CELL_SIZE 128
#define BRICK_SIZE 16

class Grid
{
private:
	static Grid* _instance;

	int numOfRow;
	int numOfColumn;
	Object ***cells;
	float deltaTime;

	void InitObjectForGrid();

	void PushObjectToVector(std::vector<Object*> * vector, Object* cell, Object * obj);
	void DeleteGrid();
	void InitGrid(int mapHeight, int mapWidth, bool isArray);
public:
	Grid();
	Grid(int mapHeight, int mapWidth, bool isArray = true);
	~Grid();

	void Add(Object *object);
	void ReSetGrid(int height, int width, bool isArray = true);
	vector<Object*>* GetCollisionObjects(Object* object);
	void UpdateGrid(Object* object);

	static Grid* GetInstance();
	static Grid* GetInstance(int mapHeight, int mapWidth, bool isArray = true);
};

