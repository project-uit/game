#include "Scence1.h"
#include "SoldierSword.h"
#include "GameDebugDraw.h"
SoldierSword* soldierSword;

Square* square;

Scence1::Scence1()
{
	this->LoadResource();
}

Scence1::~Scence1()
{

}

void Scence1::LoadResource()
{
	map = new Map();
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Camera::GetInstance()->setWorldBoundary(2048);
	soldierSword = new SoldierSword();
	square = new Square(48, 192, 528 + 16, 224);
	Grid::GetInstance(262, map->GetWidth(), false);
	Grid::GetInstance()->Add(soldierSword);
	Grid::GetInstance()->Add(square);
}

void Scence1::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence1::Render()
{
	map->drawMap();
	Scence::Render();
}