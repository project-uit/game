#pragma once
#include "Object.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include "Square.h"

using namespace std;

#define CELL_WIDTH 120
#define CELL_HEIGHT 115
#define BRICK_SIZE 16

struct  Cell
{
	int row;
	int column;
	bool isLoading;
	vector<Object*>* objects;
	Cell(int row, int column) { 
		this->row = row;
		this->column = column;
		this->objects = new vector<Object*>();
		this->isLoading = false;
	}
	~Cell() {
		for (int i = 0; i < objects->size(); i++) {
			delete objects->at(i);
		}
		objects->clear();
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
	//Ground
	vector<Square*>* squares;
	//Báo. thằng xanh lá
	vector<Object*>* randomObject;
	void DeleteGrid();
	//map Height có thể là chiều cao ô cửa sổ hoặc chiều cao của map
	void InitGrid(int mapHeight, int mapWidth, bool isArray);
	void InitObject(std::vector<Object*> * vector);
public:
	Grid();
	Grid(int mapHeight, int mapWidth, bool isArray = true);
	~Grid();
	void Add(Object *object);
	void Add(int row, int column, Object *object);
	void ReSetGrid(int height, int width, bool isArray = true);
	void GetObjectsInCells(Object* object);
	void UpdateGrid(Object* object);
	void UpdateObject(float t);
	void RenderObject();
	void AddSquare(Square* square);
	void DrawGrid();
	void LoadObjectInCell(int row, int column);
	vector<Object*>* GetObjects();
	void LoadSquares(LPCWSTR filePath);
	void LoadObjets(LPCWSTR filePath);
	void LoadFoods(LPCWSTR filePath, SCENCE scene);
	static Grid* GetInstance();
	static Grid* GetInstance(int mapHeight, int mapWidth, bool isArray = true);
};

