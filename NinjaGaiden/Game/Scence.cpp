#include "Scence.h"
#include "Player.h"
Scence::Scence()
{
	this->map = new Map();
	this->bricks = new vector<Square*>();
	this->score = 0;
	this->timer = 0;
	this->name = "";
}

Scence::~Scence()
{
	
}

void Scence::Update(float deltaTime)
{
	Grid::GetInstance()->UpdateGrid(Player::GetInstance());
	Grid::GetInstance()->UpdateObject(deltaTime);
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition());
}

void Scence::Render()
{
	//map->drawMap();
	Grid::GetInstance()->RenderObject();
}
