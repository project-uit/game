#include "Scence1.h"
#include "SoldierSword.h"
#include "GameDebugDraw.h"


Scence1::Scence1(): Scence()
{
	this->LoadResource();
}

Scence1::~Scence1()
{

}

void Scence1::LoadResource()
{
	SoldierSword* soldierSword;
	Square* square;
	Square* square1 = new Square(200, 192, 352, 224);
	Square* square2 = new Square(352, 192, 600, 224);
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Camera::GetInstance()->setWorldBoundary(2048);
	soldierSword = new SoldierSword();
	square = new Square(48, 192, 528, 224);
	Grid::GetInstance(262, map->GetWidth(), false);
	Grid::GetInstance()->Add(soldierSword);
	Grid::GetInstance()->AddSquare(square);
}

void Scence1::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence1::Render()
{
	Scence::Render();
}