#include "Scence.h"
#include "Player.h"
Scence::Scence()
{
	this->map = new Map();
	this->objects = new vector<Object*>();
	this->bricks = new vector<RECT>();
}

Scence::~Scence()
{
	
}

void Scence::Update(float deltaTime)
{
	Grid::GetInstance()->UpdateGrid(Player::GetInstance());
	Player::GetInstance()->Update(deltaTime, Grid::GetInstance()->GetObjects());
	Grid::GetInstance()->UpdateObject(deltaTime);
}

void Scence::Render()
{
	Grid::GetInstance()->RenderObject();
}

vector<Object*>* Scence::GetObjects() {
	return this->objects;
}