#pragma once
#include "Object.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include "../Object/Square/Square.h"
#include "../Logging/GameDebugDraw.h"
using namespace std;

#define CELL_WIDTH 120
#define CELL_HEIGHT 115
#define BRICK_SIZE 16

struct  Cell
{
	int row;
	int column;
	vector<Object*>* objects;
	Cell(int row, int column) {
		this->row = row;
		this->column = column;
		this->objects = new vector<Object*>();
	}
	~Cell() {
		for (int i = 0; i < objects->size(); i++) {
			delete objects->at(i);
		}
		objects->clear();
		delete objects;
	}
};

class Grid
{
private:
	static Grid* _instance;
	int numOfRow;
	int numOfColumn;
	vector<vector<Cell*>*>* cells;
	//Objects trong các cell mà Camera overlap
	vector<Object*>* objects;
	vector<Square*>* squares;
	GameDebugDraw* draw1;
	void DeleteGrid();
	//map Height có thể là chiều cao ô cửa sổ hoặc chiều cao của map
	void InitGrid(int mapHeight, int mapWidth);
public:
	Grid();
	Grid(int mapHeight, int mapWidth);
	~Grid();
	void Add(Object *object);
	void Add(int row, int column, Object *object);
	void ReSetGrid(int height, int width);
	void GetObjectsInCells(Object* object);
	void UpdateGrid(Object* object);
	void UpdateObject(float t);
	void UpdatePlayer(float t);
	void RenderObject();
	void DrawGrid();
	vector<Object*>* GetObjects();
	vector<Object*>* FilterObjects(OBJECT_TYPE object);
	bool FindObject(Object* objects);
	void LoadGroundAndItem(LPCWSTR filePath, SCENCE scene);
	void LoadObjects(LPCWSTR filePath);
	static Grid* GetInstance();
	static Grid* GetInstance(int mapHeight, int mapWidth, bool isArray = true);
};

