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
	Cell(int row, int column) { 
		this->row = row;
		this->column = column;
	}
	static bool FindCell(vector<Cell*>* cells, Cell* cell) {
		bool flag = false;
		for (int i = 0; i < cells->size(); i++) {
			int col_1 = cells->at(i)->column;
			int row_1 = cells->at(i)->row;
			if (col_1 == cell->column && row_1 == cell->row) {
				flag = true;
				break;
			}
		}
		return flag;
	}
};

class Grid
{
private:
	static Grid* _instance;
	int numOfRow;
	int numOfColumn;
	vector<vector<vector<Object*>*>*>* cells;
	vector<Cell*>* cellLoading;
	//Objects trong các cell mà Camera overlap
	vector<Object*>* objects;
	//Ground
	vector<Square*>* squares;
	//Báo. thằng xanh lá
	vector<Object*>* randomObject;
	float deltaTime;
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
	static Grid* GetInstance();
	static Grid* GetInstance(int mapHeight, int mapWidth, bool isArray = true);
};

