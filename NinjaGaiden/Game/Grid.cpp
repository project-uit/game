﻿#include "Grid.h"


Grid* Grid::_instance = NULL;


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

void Grid::InitObjectForGrid()
{
	this->cells = new Object**[this->numOfRow];

	for (int row = 0; row < this->numOfRow; row++) {
		this->cells[row] = new Object*[this->numOfColumn];

		for (int column = 0; column < this->numOfColumn; column++) {
			this->cells[row][column] = NULL;
		}
	}
}

void Grid::PushObjectToVector(std::vector<Object*>* vector, Object * cell, Object* obj)
{
	while (cell != NULL) {

		if (cell != obj) {
			vector->push_back(cell);
		}
		cell = cell->GetNextObj();
	}
}

void Grid::DeleteGrid()
{
	for (int row = 0; row < this->numOfRow; row++) {
		for (int column = 0; column < this->numOfColumn; column++) {
			while (this->cells[row][column] != NULL) {
				Object* temp = this->cells[row][column];
				this->cells[row][column] = this->cells[row][column]->GetNextObj();
				this->cells[row][column]->SetPreObj(NULL);

				temp->SetNextObj(NULL);

				if (temp->GetObjectType() != MAIN_CHARACTER) {
					delete temp;
				}
			}

			if (this->cells[row][column] == NULL)
				delete this->cells[row][column];
		}
		delete[] this->cells[row];
	}

	delete[] this->cells;
}

void Grid::InitGrid(int mapHeight, int mapWidth, bool isArray)
{
	if (isArray) {
		this->numOfRow = (int)ceil((float)mapHeight * BRICK_SIZE / CELL_SIZE);
		this->numOfColumn = (int)ceil((float)mapWidth * BRICK_SIZE / CELL_SIZE);
	}
	else {
		this->numOfRow = (int)ceil((float)mapHeight / CELL_SIZE);
		this->numOfColumn = (int)ceil((float)mapWidth / CELL_SIZE);
	}

	this->InitObjectForGrid();
}

void Grid::Add(Object * obj)
{
	// Lưu lại giá trị cũ của object sau mỗi lần update
	obj->SetLastPos(obj->GetPosition());


	// Xác định object đang nằm ở grid nào
	int column = floor(obj->GetPosition().x / CELL_SIZE);
	int row = floor(obj->GetPosition().y / CELL_SIZE);

	// Thêm object vào đầu dslk
	obj->SetPreObj(NULL);
	obj->SetNextObj(this->cells[row][column]);
	this->cells[row][column] = obj;

	if (obj->GetNextObj() != NULL) {
		obj->GetNextObj()->SetPreObj(obj);
	}
}

void Grid::ReSetGrid(int height, int width, bool isArray)
{
	this->DeleteGrid();
	this->InitGrid(height, width, isArray);
}

vector<Object*>* Grid::GetCollisionObjects(Object * object)
{
	vector<Object*> *objects = new std::vector<Object*>();

	if (object == nullptr || object->GetObjectType() == BRICK)
		return objects;

	int row = (int)floor(object->GetPosition().y / CELL_SIZE);
	int column = (int)floor(object->GetPosition().x / CELL_SIZE);

	// Lấy object ở cell hiện tại
	this->PushObjectToVector(objects, this->cells[row][column], object);

	// Lấy các cell ở kế bên

	// Nếu đang đi qua trái
	if (object->GetVeclocity().x < 0) {
		if (column > 0) this->PushObjectToVector(objects, this->cells[row][column - 1], object); // Bên trái

		if (column > 0 && row > 0) this->PushObjectToVector(objects, this->cells[row - 1][column - 1], object); // Trái trên

		if (column > 0 && row < this->numOfRow - 1) this->PushObjectToVector(objects, this->cells[row + 1][column - 1], object); //Trái dưới
	}

	// Nếu đang đi qua phải
	else {
		if (column < this->numOfColumn - 1) this->PushObjectToVector(objects, this->cells[row][column + 1], object); //Bên phải

		if (column < this->numOfColumn - 1 && row > 0) this->PushObjectToVector(objects, this->cells[row - 1][column + 1], object); // Phải trên

		if (column < this->numOfColumn - 1 && row < this->numOfRow - 1) this->PushObjectToVector(objects, this->cells[row + 1][column + 1], object); // Phải dưới
	}

	// Nếu đang đi lên
	if (object->GetVeclocity().y < 0) {
		if (row > 0) this->PushObjectToVector(objects, this->cells[row - 1][column], object);
	}
	// Nếu đang đi xuống
	else {
		if (row < this->numOfRow - 1) this->PushObjectToVector(objects, this->cells[row + 1][column], object);
	}

	return objects;
}

void Grid::UpdateGrid(Object * object)
{
	// Kiểm tra xem có thay đổi cell hay không
	int oldRow = floor(object->GetLastPos().y / CELL_SIZE);
	int oldColumn = floor(object->GetLastPos().x / CELL_SIZE);

	int newRow = floor(object->GetPosition().y / CELL_SIZE);
	int newColumn = floor(object->GetPosition().x / CELL_SIZE);

	// Nếu không thay đổi thì thoát ra
	if (oldRow == newRow && oldColumn == newColumn)
		return;

	// Xóa object ra khỏi cell hiện tại và cập nhật lại cell mới
	if (object->GetPreObj() != NULL) {
		object->GetPreObj()->SetNextObj(object->GetNextObj());
	}
	if (object->GetNextObj() != NULL) {
		object->GetNextObj()->SetPreObj(object->GetPreObj());
	}

	// Nếu object đang đứng đầu
	if (cells[oldRow][oldColumn] == object) {
		cells[oldRow][oldColumn] = object->GetNextObj();
	}

	this->Add(object);
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