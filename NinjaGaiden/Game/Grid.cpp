#include "Grid.h"
#include "Camera.h"
#include "Debug.h"
#include "GameDebugDraw.h"
#include "SoldierSword.h"
Grid* Grid::_instance = NULL;
GameDebugDraw* draw1;

Grid::Grid()
{
	
}

Grid::Grid(int mapHeight, int mapWidth, bool isArray)
{
	draw1 = new GameDebugDraw();
	this->InitGrid(mapHeight, mapWidth, isArray);
	squares = new  vector<Square*>();
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
	squares->clear();
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
	
	//add object player
	objects->push_back(object);

	//Cách lấy index của grid từ vị trí object
	int row = (int)floor(object->GetPosition().y / CELL_HEIGHT);
	int column = (int)floor(object->GetPosition().x / CELL_WIDTH);

	//Lấy bound của Cam để xét với từng cell bị overlap
	RECT camREC  = Camera::GetInstance()->GetRECT();

	//góc trái trên
	int x1 = int(camREC.left/ CELL_WIDTH), y1 = int(camREC.top/CELL_HEIGHT);
	//góc phải dưới
	int x2 = int(camREC.right/ CELL_WIDTH), y2 = int(camREC.bottom/ CELL_HEIGHT);
	//Add square
	for (int i = 0; i < squares->size(); i++) {
		if (Game::AABB(camREC, squares->at(i)->GetBoundingBox())) {
			this->objects->push_back(squares->at(i));
		}
	}

	//dòng của grid
	for (int i = y1; i < y2; i++) {
		//cột của grid
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

void Grid::AddSquare(Square* s) {
	squares->push_back(s);
}

void Grid::LoadSquares(LPCWSTR filePath) {
	fstream f;
	try
	{
		f.open(filePath);
	}
	catch (fstream::failure e)
	{
		trace(L"Error when init grid %s", filePath);
		return;
	}
	string line;
	while (!f.eof()) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> * tempVector = new vector<int>();

		while (getline(iss, splitString, '\t'))
		{
			tempVector->push_back(stoi(splitString));
		}
		if (tempVector->size() > 1) {
			int left = tempVector->at(0), top = tempVector->at(1),
				right = tempVector->at(2), bottom = tempVector->at(3);
			Square* square = new Square(left, top, right, bottom);
			squares->push_back(square);
		}
		tempVector->clear();
		delete tempVector;
	}
	f.close();
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

void Grid::LoadObjets(LPCWSTR filePath) {
	fstream f;
	try
	{
		f.open(filePath);
	}
	catch (fstream::failure e)
	{
		trace(L"Error when init grid %s", filePath);
		return;
	}
	string line;
	while (!f.eof()) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> * tempVector = new vector<int>();

		while (getline(iss, splitString, '\t'))
		{
			tempVector->push_back(stoi(splitString));
		}
		if (tempVector->size() > 1) {
			int id = tempVector->at(0);
			int TypeObject = tempVector->at(1);
			int positionX = tempVector->at(2);
			int positionY = tempVector->at(3);
			int direction = tempVector->at(4);//0: left, 1: right
			DIRECTION direct = direction == 0 ? LEFT : RIGHT;
			RECT movingArea;
			if (tempVector->size() > 5) {
				int left = tempVector->at(5);
				int top = tempVector->at(6);
				int right = tempVector->at(7);
				int bottom = tempVector->at(8);
				SetRect(&movingArea, left, top, right, bottom);
			}
			Object* object;
			switch (TypeObject) {
				case 1:
					object = new SoldierSword(movingArea, positionX, positionY, direct);
					Add(object);
					break;
				case 2:
					break;
				default:
					break;
			}
		}
	}
	f.close();
}