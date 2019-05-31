#include "Scence2.h"
#include "Mp3.h"
#include "HUD.h"
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
	Player::GetInstance()->SetPosition(1920, 0);
	Player::GetInstance()->SetHp(16);
	name = " STAGE 3-2";
	scenceType = SCENCE::SCENCE_2;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_2, PATH_TEXTURE_MAP_2, ID_TEXTURE_MAP_2);
	Camera::GetInstance()->setWorldBoundary(3072);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth());
	Grid::GetInstance()->LoadSquares(PATH_POS_GROUND_MAP_2);
	Grid::GetInstance()->LoadObjects(PATH_POS_ENEMY_MAP_2);
	Grid::GetInstance()->LoadFoods(PATH_POS_FOOD_MAP_2, scenceType);
	Grid::GetInstance()->LoadLadders(PATH_POS_LADDER_MAP_2);
	Grid::GetInstance()->LoadRocks(PATH_POS_ROCK_MAP_2);
	Grid::GetInstance()->LoadBricks(PATH_POS_BRICK_MAP_2);

	//Mp3 mp3;
	//mp3.PlaySoundTrack(SOUND_TRACK_PATH_MAP_2);
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