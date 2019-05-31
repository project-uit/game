#include "Scence1.h"
#include "MP3Player.h"
#include "Sound.h"
#include "SoldierSword.h"
#include "GameDebugDraw.h"
#include "HUD.h"

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
	Player::GetInstance()->SetLastPos({ -1.0f, -1.0f, 0 });
	Player::GetInstance()->SetPosition(1141, 100.0f);
	name = " STAGE 3-1";
	scenceType = SCENCE::SCENCE_1;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Camera::GetInstance()->setWorldBoundary(2048);
	Grid::GetInstance()->ReSetGrid(246, map->GetWidth());
	Grid::GetInstance()->LoadSquares(PATH_POS_GROUND_MAP_1);
	Grid::GetInstance()->LoadObjects(PATH_POS_ENEMY_MAP_1);
	Grid::GetInstance()->LoadFoods(PATH_POS_FOOD_MAP_1, scenceType);
	waitingTime = 0;
	/*Mp3 mp3;
	mp3.PlaySoundTrack(SOUND_TRACK_PATH_MAP_1);*/
	//Sound::GetInstance()->LoadSound(SOUND_TRACK_PATH_MAP_1, SOUND_TRACK_MAP1);
	//Sound::GetInstance()->Play(SOUND_TRACK_MAP1, true, 0);
}

void Scence1::Update(float deltaTime)
{
	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE
		&& Player::GetInstance()->GetLifePoint() == 0) {
		return;
	}
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition());
	Grid::GetInstance()->UpdateGrid(Player::GetInstance());
	Grid::GetInstance()->UpdateObject(deltaTime);
	HUD::GetInstance()->Update(deltaTime);
	if (time >= 1.0f) {
		this->timer--;
		time = 0;
		Player::GetInstance()->MinusFreezeTime();
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

void Scence1::Render()
{
	HUD::GetInstance()->Render();
	Scence::Render();
}