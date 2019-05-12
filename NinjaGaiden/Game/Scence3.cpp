#include "Scence3.h"
Scence3::Scence3() : Scence()
{
	this->LoadResource();
}

Scence3::~Scence3()
{
	delete map;
}

void Scence3::LoadResource()
{
	Player::GetInstance()->SetLastPos({ -1.0f, -1.0f, 0 });
	Player::GetInstance()->SetPosition(3.0, 100.0f);
	name = " STAGE 3-3";
	scenceType = SCENCE::SCENCE_3;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_3, PATH_TEXTURE_MAP_3, ID_TEXTURE_MAP_3);
	Camera::GetInstance()->setWorldBoundary(256);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth(), false);
	Grid::GetInstance()->LoadSquares(PATH_POS_GROUND_MAP_3);
	//Grid::GetInstance()->LoadObjets(PATH_POS_ENEMY_MAP_1);
}

void Scence3::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence3::Render()
{
	Scence::Render();
}