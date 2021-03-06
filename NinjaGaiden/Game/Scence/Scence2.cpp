#include "Scence2.h"
#include "../HUD/HUD.h"
#include "../Framework/World.h"
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
	Player::GetInstance()->Restart(2815, 0);
	name = " STAGE 3-2";
	scenceType = SCENCE::SCENCE_2;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_2, PATH_TEXTURE_MAP_2, ID_TEXTURE_MAP_2);
	Camera::GetInstance()->setWorldBoundary(3072);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth());
	Grid::GetInstance()->LoadGroundAndItem(PATH_POS_GROUND_MAP_2, scenceType);
	Grid::GetInstance()->LoadObjects(PATH_POS_ENEMY_MAP_2);
}

void Scence2::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence2::Render()
{
	HUD::GetInstance()->Render();
	Scence::Render();
}