﻿#pragma once
#include "Object.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define CELL_WIDTH 84
#define CELL_HEIGHT 131
#define BRICK_SIZE 16

class Grid
{
private:
	static Grid* _instance;

	int numOfRow;
	int numOfColumn;
	vector<vector<vector<Object*>*>*>* cells;
	//Objects trong các cell mà Camera overlap
	vector<Object*>* objects;
	float deltaTime;
	void PushObjectToVector(std::vector<Object*> * vector, Object* cell, Object * obj);
	void DeleteGrid();
	void InitGrid(int mapHeight, int mapWidth, bool isArray);
	void InitObject(std::vector<Object*> * vector);
public:
	Grid();
	Grid(int mapHeight, int mapWidth, bool isArray = true);
	~Grid();
	void Add(Object *object);
	void ReSetGrid(int height, int width, bool isArray = true);
	void GetObjectsInCells(Object* object);
	void UpdateGrid(Object* object);
	void UpdateObject(float t);
	void RenderObject();
	vector<Object*>* GetObjects();
	static Grid* GetInstance();
	static Grid* GetInstance(int mapHeight, int mapWidth, bool isArray = true);
};

