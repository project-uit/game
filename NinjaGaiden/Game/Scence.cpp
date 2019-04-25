#include "Scence.h"
#include "Player.h"
Scence::Scence()
{
	this->map = new Map();
	this->bricks = new vector<Square*>();
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
