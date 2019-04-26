#include "Grid.h"
#include "Camera.h"
#include "Debug.h"
#include "GameDebugDraw.h"
Grid* Grid::_instance = NULL;
GameDebugDraw* draw1;

Grid::Grid()
{
	
}

Grid::Grid(int mapHeight, int mapWidth, bool isArray)
{
	draw1 = new GameDebugDraw();
	this->InitGrid(mapHeight, mapWidth, isArray);
	cells = new vector<vector<vector<Object*>*>*>();
	objects = new vector<Object*>();
	cells->reserve(numOfRow);
	for (size_t i = 0; i < numOfRow; i++) {
		vector<vector<Object*>*> * tempList = new vector<vector<Object*>*>();
		tempList->reserve(numOfColumn);
		for (size_t j = 0; j < numOfColumn; j++) {
			vector<Object*>* obj = new vector<Object*>();
			tempList->push_back(obj);
		}
		cells->push_back(tempList);
	}
}

Grid::~Grid()
{
	this->DeleteGrid();
}

void Grid::InitObject(std::vector<Object*> * vt) {
	
	for(int i = 0; i < vt->size(); i++) {
		Add(vt->at(i));
	}
}

void Grid::DeleteGrid()
{
	for (int i = 0; i < cells->size(); i++) {
		for (int j = 0; j < cells->at(i)->size(); j++) {
			for (int k = 0; k < cells->at(i)->at(j)->size(); k++) {
				delete cells->at(i)->at(j)->at(k);
			}
			delete cells->at(i)->at(j);
		}
		delete cells->at(i);
	}
	delete cells;
	objects->clear();
}

void Grid::InitGrid(int mapHeight, int mapWidth, bool isArray)
{
	this->numOfRow = (int)ceil((float)mapHeight / CELL_HEIGHT);
	this->numOfColumn = (int)ceil((float)mapWidth / CELL_WIDTH);
}

void Grid::Add(Object * obj)
{
	obj->SetLastPos(obj->GetPosition());
	int column = floor(obj->GetPosition().x / CELL_WIDTH);
	int row = floor(obj->GetPosition().y / CELL_HEIGHT);
	cells->at(row)->at(column)->push_back(obj);
}

void Grid::ReSetGrid(int height, int width, bool isArray)
{
	this->DeleteGrid();
	this->InitGrid(height, width, isArray);
}

void Grid::GetObjectsInCells(Object * object)
{
	if (objects->size() > 0)
		return;

	if (object == nullptr)
		return;
	//Cách lấy index của grid từ vị trí object
	int row = (int)floor(object->GetPosition().y / CELL_HEIGHT);
	int column = (int)floor(object->GetPosition().x / CELL_WIDTH);
	//Lấy bound của Cam để xét với từng cell bị overlap
	RECT camREC  = Camera::GetInstance()->GetRECT();

	//góc trái trên
	int x1 = int(camREC.left/ CELL_WIDTH), y1 = int(camREC.top/CELL_HEIGHT);
	//góc phải dưới
	int x2 = int(camREC.right/ CELL_WIDTH), y2 = int(camREC.bottom/ CELL_HEIGHT);

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			vector<Object*> *listObj = cells->at(i)->at(j);
			for (int k = 0; k < listObj->size(); k++) {
				this->objects->push_back(listObj->at(k));
			}
		}
	}
}

void Grid::UpdateGrid(Object * object)
{
	int oldRow = floor(object->GetLastPos().y / CELL_HEIGHT);
	int oldColumn = floor(object->GetLastPos().x / CELL_WIDTH);

	int newRow = floor(object->GetPosition().y / CELL_HEIGHT);
	int newColumn = floor(object->GetPosition().x / CELL_WIDTH);
	if (oldRow == newRow && oldColumn == newColumn)
		return;
	objects->clear();
	GetObjectsInCells(object);
}

void Grid::UpdateObject(float t) {
	for (int i = 0; i < objects->size(); i++) {
		objects->at(i)->Update(t, objects);
	}
}

void Grid::RenderObject() {
	for (int i = 0; i < objects->size(); i++) {
		objects->at(i)->Render();
		draw1->DrawRect(objects->at(i)->GetBoundingBox(), Camera::GetInstance());
	}
}

Grid * Grid::GetInstance()
{
	if (_instance == NULL) _instance = new Grid();
	return _instance;
}

Grid * Grid::GetInstance(int mapHeight, int mapWidth, bool isArray)
{
	if (_instance == NULL) _instance = new Grid(mapHeight, mapWidth, isArray);
	return _instance;
}

vector<Object*>* Grid::GetObjects() {
	return objects;
}