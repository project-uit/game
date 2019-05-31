#include "Scence3.h"
#include "HUD.h"
Scence3::Scence3() : Scence()
{
	this->LoadResource();
}

Scence3::~Scence3()
{
	delete map;
	delete boss;
}

void Scence3::LoadResource()
{
	Player::GetInstance()->SetLastPos({ -1.0f, -1.0f, 0 });
	Player::GetInstance()->SetPosition(125.0f, 130.0f);
	Player::GetInstance()->SetHp(16);
	name = " STAGE 3-3";
	scenceType = SCENCE::SCENCE_3;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_3, PATH_TEXTURE_MAP_3, ID_TEXTURE_MAP_3);
	Camera::GetInstance()->setWorldBoundary(256);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth());
	Grid::GetInstance()->LoadSquares(PATH_POS_GROUND_MAP_3);
	Grid::GetInstance()->LoadRocks(PATH_POS_ROCK_MAP_3);
	boss = new Boss();
	Grid::GetInstance()->Add(boss);
	remainTime = 1.0f;
}

void Scence3::Update(float deltaTime)
{
	if (boss->GetHp() == 0) {
		remainTime = 0.05f;
	}

	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE
		&& Player::GetInstance()->GetLifePoint() == 0) {
		return;
	}
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition());
	Grid::GetInstance()->UpdateGrid(Player::GetInstance());
	Grid::GetInstance()->UpdateObject(deltaTime);
	HUD::GetInstance()->Update(deltaTime);
	
	if (time >= remainTime) {
		if (boss->GetHp() == 0 && this->timer > 0) {
			Player::GetInstance()->AddScore(200);
		}
		this->timer--;
		time = 0;
		if (this->timer <= 0) {
			this->timer = 0;
		}
	}
	else {
		time += deltaTime;
	}
	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE) {
		this->timer = 150;
	}
}

void Scence3::Render()
{
	HUD::GetInstance()->Render(boss->GetHp());
	Scence::Render();
}