#include "Scence1.h"
#include "SoldierSword.h"
#include "GameDebugDraw.h"
#include "HUD.h"
#include "World.h"
#include "MCIPlayer.h"
Scence1::Scence1(): Scence()
{
	this->LoadResource();
}

Scence1::~Scence1()
{
	delete map;
}

void Scence1::LoadResource()
{
	Player::GetInstance()->Restart(1200, 100.0f);
	name = " STAGE 3-1";
	scenceType = SCENCE::SCENCE_1;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Camera::GetInstance()->setWorldBoundary(2048);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth());
	Grid::GetInstance()->LoadGroundAndItem(PATH_POS_GROUND_MAP_1, scenceType);
	Grid::GetInstance()->LoadObjects(PATH_POS_ENEMY_MAP_1);
}

void Scence1::Update(float deltaTime)
{
	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE
		&& Player::GetInstance()->GetLifePoint() == 0) {
		return;
	}
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition());
	Grid::GetInstance()->UpdateGrid(Player::GetInstance());
	if (Player::GetInstance()->GetAlphaEndPoint() < 255) {
		Grid::GetInstance()->UpdatePlayer(deltaTime);
	}
	else {
		Grid::GetInstance()->UpdateObject(deltaTime);
	}
	HUD::GetInstance()->Update(deltaTime);
	if (time >= 1.0f) {
		this->timer--;
		time = 0;
		Player::GetInstance()->MinusFreezeTime();
		if (this->timer <= 0) {
			this->timer = 0;
			Player::GetInstance()->SetState(PLAYER_STATE::DIE);
		}
	}
	else {
		time += deltaTime;
	}
	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE) {
		this->timer = 150;
	}
}

void Scence1::Render()
{
	HUD::GetInstance()->Render();
	Scence::Render();
}