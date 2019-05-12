#include "Scence2.h"
Scence2::Scence2() : Scence()
{
	this->LoadResource();
}

Scence2::~Scence2()
{
	delete map;
}

void Scence2::LoadResource()
{
	Player::GetInstance()->SetLastPos({ -1.0f, -1.0f, 0 });
	Player::GetInstance()->SetPosition(3.0, 100.0f);
	name = " STAGE 3-2";
	scenceType = SCENCE::SCENCE_2;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_2, PATH_TEXTURE_MAP_2, ID_TEXTURE_MAP_2);
	Camera::GetInstance()->setWorldBoundary(3072);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth(), false);
	Grid::GetInstance()->LoadSquares(PATH_POS_GROUND_MAP_2);
	//Grid::GetInstance()->LoadObjets(PATH_POS_ENEMY_MAP_1);
}

void Scence2::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence2::Render()
{
	Scence::Render();
}