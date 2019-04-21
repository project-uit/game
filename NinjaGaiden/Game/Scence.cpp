#include "Scence.h"
Scence::Scence()
{
	this->map = new Map();
	this->objects = new vector<Object*>();
	this->bricks = new vector<RECT>();
}

Scence::~Scence()
{
}

void Scence::InitHorizontalBrick(RECT rect)
{
	int n = floor(rect.left / CELL_SIZE);
	int tempRight = (n + 1) * CELL_SIZE;
	if (tempRight > rect.right) {
		this->InitVerticalBrick(rect);
		return;
	}
	else {
		RECT rect1;
		rect1.top = rect.top;
		rect1.left = rect.left;
		rect1.right = tempRight;
		rect1.bottom = rect.bottom;
		this->InitVerticalBrick(rect1);

		RECT rect2;
		rect2.top = rect.top;
		rect2.left = tempRight;
		rect2.bottom = rect.bottom;
		rect2.right = rect.right;

		this->InitHorizontalBrick(rect2);
	}
}

void Scence::InitVerticalBrick(RECT rect)
{
	int n = floor(rect.top / CELL_SIZE);
	int tempBottom = (n + 1) * CELL_SIZE;
	if (tempBottom > rect.bottom) {
		this->bricks->push_back(rect);
		return;
	}
	else {
		RECT rect1;
		rect1.top = rect.top;
		rect1.left = rect.left;
		rect1.right = rect.right;
		rect1.bottom = tempBottom;
		this->bricks->push_back(rect1);

		RECT rect2;
		rect2.top = tempBottom;
		rect2.left = rect.left;
		rect2.bottom = rect.bottom;
		rect2.right = rect.right;

		this->InitVerticalBrick(rect2);
	}
}

void Scence::Update(float deltaTime)
{
	//for (int i = 0; i < this->objects->size(); i++) {

	//	if (this->objects->at(i)->GetObjectType() != OBJECT_TYPE::SQUARE) {
	//		vector<Object*>* collisionsObject = Grid::GetInstance()->GetCollisionObjects(this->objects->at(i));

	//		this->objects->at(i)->Update(deltaTime, collisionsObject);

	//		for (int j = 0; j < collisionsObject->size(); j++) {
	//			Grid::GetInstance()->UpdateGrid(collisionsObject->at(j));
	//		}

	//	}
	//	else {
	//		this->objects->at(i)->Update(deltaTime, NULL);
	//	}

	//	Grid::GetInstance()->UpdateGrid(this->objects->at(i));


	//}
}

void Scence::Render()
{
	for (int i = 0; i < this->objects->size(); i++) {
		this->objects->at(i)->Render();
	}
}

vector<Object*>* Scence::GetObjects() {
	return this->objects;
}