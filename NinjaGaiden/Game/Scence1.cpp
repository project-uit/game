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
	scenceType = SCENCE::SCENCE_1;
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Camera::GetInstance()->setWorldBoundary(2048);
	Grid::GetInstance(246, map->GetWidth(), false);
	Grid::GetInstance()->LoadSquares(PATH_POS_GROUND_MAP_1);
	Grid::GetInstance()->LoadObjets(PATH_POS_ENEMY_MAP_1);
}

void Scence1::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence1::Render()
{
	Scence::Render();
}