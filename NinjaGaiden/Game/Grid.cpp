#include <algorithm>
#include "Grid.h"
#include "Camera.h"
#include "Debug.h"
#include "GameDebugDraw.h"
#include "Player.h"
#include "Food.h"
#include "SoldierSword.h"
#include "SoliderGun.h"
#include "SoliderBazoka.h"
#include "Witch.h"
#include "Panther.h"
#include "Eagle.h"
#include <math.h> 
Grid* Grid::_instance = NULL;
GameDebugDraw* draw1;

Grid::Grid()
{
	
}

Grid::Grid(int mapHeight, int mapWidth, bool isArray)
{
	this->InitGrid(mapHeight, mapWidth, isArray);
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
	if (cells) {
		for (int i = 0; i < cells->size(); i++) {
			for (int j = 0; j < cells->at(i)->size(); j++) {
				delete cells->at(i)->at(j);
			}
			cells->at(i)->clear();
			delete cells->at(i);
		}
		delete cells;
	}

	if (objects) {
		objects->clear();
		delete objects;
	}

	if (squares) {
		squares->clear();
		delete squares;
	}

	if (randomObject) {
		randomObject->clear();
		delete randomObject;
	}
}

void Grid::InitGrid(int mapHeight, int mapWidth, bool isArray)
{
	draw1 = new GameDebugDraw();
	this->numOfRow = (int)ceil((float)mapHeight / CELL_HEIGHT);
	this->numOfColumn = (int)ceil((float)mapWidth / CELL_WIDTH);
	squares = new  vector<Square*>();
	cells = new vector<vector<Cell*>*>();
	objects = new vector<Object*>();
	randomObject = new vector<Object*>();
	cells->reserve(numOfRow);
	for (size_t i = 0; i < numOfRow; i++) {
		vector<Cell*> * tempList = new vector<Cell*>();
		tempList->reserve(numOfColumn);
		for (size_t j = 0; j < numOfColumn; j++) {
			Cell* cell = new Cell(i, j);
			tempList->push_back(cell);
		}
		cells->push_back(tempList);
	}
}

void Grid::Add(Object * obj)
{
	obj->SetLastPos(obj->GetPosition());
	int column = floor(obj->GetPosition().x / CELL_WIDTH);
	int row = floor(obj->GetPosition().y / CELL_HEIGHT);
	cells->at(row)->at(column)->objects->push_back(obj);
}

void Grid::Add(int row, int column, Object * obj) {
	obj->SetLastPos(obj->GetPosition());
	cells->at(row)->at(column)->objects->push_back(obj);
}

void Grid::ReSetGrid(int height, int width, bool isArray)
{
	this->DeleteGrid();
	this->InitGrid(height, width, isArray);
}

void Grid::LoadObjectInCell(int row, int column) {

}

void Grid::GetObjectsInCells(Object * object)
{
	/*if (objects->size() > 0)
		return;*/

	if (object == nullptr)
		return;
	
	//vector<Cell>* tempObjects = new vector<Cell>();
	//for (int i = 0; i < objects->size(); i++) {
	//	if (Game::AABB(objects->at(i)->GetBoundingBox(), camREC)) {
	//		
	//	}
	//}
	objects->clear();
	//add object player
	objects->push_back(object);

	//int row = (int)floor(object->GetPosition().y / CELL_HEIGHT);
	//int column = (int)floor(object->GetPosition().x / CELL_WIDTH);

	//Lấy bound của Cam để xét với từng cell bị overlap
	RECT camREC = Camera::GetInstance()->GetRECT();
	//góc trái trên
	int x1 = ceil(camREC.left/ CELL_WIDTH), y1 = ceil(camREC.top/CELL_HEIGHT);
	//góc phải dưới
	int x2 = ceil(camREC.right/ CELL_WIDTH), y2 = ceil(camREC.bottom/ CELL_HEIGHT);
	//Add square
	for (int i = 0; i < squares->size(); i++) {
		if (Game::AABB(camREC, squares->at(i)->GetBoundingBox())) {
			this->objects->push_back(squares->at(i));
		}
	}
	RECT camRECTx = Camera::GetInstance()->GetRECTx();
	//Add báo, lính xanh lá
	for (int i = 0; i < randomObject->size(); i++) {
		if (Game::AABB(camRECTx, randomObject->at(i)->GetBoundingBox())) {
			this->objects->push_back(randomObject->at(i));
		}
		else {
			if (randomObject->at(i)->GetActive()) {
				randomObject->at(i)->ResetState();
			}
		}
	}

	int xRs = x2;
	if (xRs < numOfColumn) {
		for (int i = y1; i < y2; i++) {
			if (cells->at(i)->at(xRs)->isLoading) {
				vector<Object*> *listObj = cells->at(i)->at(xRs)->objects;
				for (int k = 0; k < listObj->size(); k++) {
					if (Game::AABB(Camera::GetInstance()->GetRECTx(), listObj->at(k)->GetBoundingBox())) {
						listObj->at(k)->ResetState();
					}
				}
				cells->at(i)->at(xRs)->isLoading = false;
			}
		}
	}
	xRs = x1 - 1;
	if (xRs >= 0) {
		for (int i = y1; i < y2; i++) {
			if (cells->at(i)->at(xRs)->isLoading) {
				vector<Object*> *listObj = cells->at(i)->at(xRs)->objects;
				for (int k = 0; k < listObj->size(); k++) {
					if (Game::AABB(Camera::GetInstance()->GetRECTx(), listObj->at(k)->GetBoundingBox())) {
						listObj->at(k)->ResetState();
					}
				}
				cells->at(i)->at(xRs)->isLoading = false;
			}
		}
	}
	
	//dòng của grid
	for (int i = y1; i < y2; i++) {
		//cột của grid
		for (int j = x1; j < x2; j++) {
			vector<Object*> *listObj = cells->at(i)->at(j)->objects;
			for (int k = 0; k < listObj->size(); k++) {
				if (Game::AABB(Camera::GetInstance()->GetRECTx(), listObj->at(k)->GetBoundingBox())) {
					this->objects->push_back(listObj->at(k));
					cells->at(i)->at(j)->isLoading = true;
				}
				else {
					listObj->at(k)->ResetState();
				}
			}
		}
	}
}

void Grid::UpdateGrid(Object * object)
{
	int oldRow = floor(object->GetLastPos().y / CELL_HEIGHT);
	int oldColumn = floor(object->GetLastPos().x / CELL_WIDTH);

	int newRow = ceil((object->GetPosition().y / CELL_HEIGHT));
	int newColumn = ceil((object->GetPosition().x / CELL_WIDTH));
	if (oldRow == newRow && oldColumn == newColumn) {
		return;
	}
	
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
	//DrawGrid();
	//draw1->DrawRect(Camera::GetInstance()->GetRECT(), Camera::GetInstance());
	//draw1->DrawRect(Player::GetInstance()->GetKatana()->GetBoundingBox(), Camera::GetInstance());
}

void Grid::DrawGrid() {
	RECT camREC = Camera::GetInstance()->GetRECT();
	//góc trái trên
	int x1 = ceil(camREC.left / CELL_WIDTH), y1 = ceil(camREC.top / CELL_HEIGHT);
	//góc phải dưới
	int x2 = ceil(camREC.right / CELL_WIDTH), y2 = ceil(camREC.bottom / CELL_HEIGHT);
	
	for (int i = y1; i < y2; i++) {
		//cột của grid
		for (int j = x1; j < x2; j++) {
			RECT r;
			SetRect(&r, j*CELL_WIDTH, i*CELL_HEIGHT
				, (j + 1)*CELL_WIDTH, (i + 1)*CELL_HEIGHT);
			draw1->DrawRect(r, Camera::GetInstance());
		}
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
			vector<int> movingLimit, activeArea;
			//RECT movingArea, movingBox;
			if (tempVector->size() > 4) {
				//======== movingLimit
				//==== Vùng di chuyển khi direction object là left
				int left = tempVector->at(4); 
				int right = tempVector->at(5);
				movingLimit.push_back(left);
				movingLimit.push_back(right);
				//==== Vùng di chuyển khi direction object là right
				left = tempVector->at(6);
				right = tempVector->at(7);				
				movingLimit.push_back(left);
				movingLimit.push_back(right);
				//======== activeArea
				//==== Vùng kích hoạt khi direction object là left
				left = tempVector->at(8);
				right = tempVector->at(9);
				activeArea.push_back(left);
				activeArea.push_back(right);
				//==== Vùng kích hoạt khi direction object là right
				left = tempVector->at(10);
				right = tempVector->at(11);
				activeArea.push_back(left);
				activeArea.push_back(right);
			}
			int row = 0; // dòng muốn add vào grid (chỉ dùng cho các object đặc biệt)
			int column = 0; // cột muốn add vào grid (chỉ dùng cho các object đặc biệt)
			if (tempVector->size() > 12) {
				row = tempVector->at(13);
				column = tempVector->at(12);
			}
			Object* object;
			switch (TypeObject) {
				case 1:
					object = new SoldierSword(movingLimit, activeArea, positionX, positionY);
					Add(object);
					break;
				case 2:
					object = new Witch(positionX, positionY, movingLimit, activeArea);
					Add(object);
					break;
				case 3:
					object = new SoliderGun(positionX, positionY, movingLimit, activeArea);
					Add(row, column, object);
					break;
				case 4:
					object = new Panther(movingLimit, activeArea, positionX, positionY);
					object->SetLastPos(object->GetPosition());
					randomObject->push_back(object);
					break;
				case 5:
					object = new SoliderBazoka(positionX, positionY, movingLimit, activeArea);
					Add(object);
					break;
				case 10:
					object = new Eagle(activeArea, positionX, positionY);
					object->SetLastPos(object->GetPosition());
					randomObject->push_back(object);
					break;
				default:
					break;
			}
		}
		tempVector->clear();
		delete tempVector;
	}
	f.close();
}

void Grid::LoadFoods(LPCWSTR filePath, SCENCE scene) {
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
			vector<int> movingLimit, activeArea;

			int row = 0;
			int column = 0;
			if (tempVector->size() > 12) {

			}
			Object* object;
			object = new Food(scene, TypeObject, positionX, positionY);
			Add(object);
		}
		tempVector->clear();
		delete tempVector;
	}
	f.close();
}