#include "World.h"
#include <string.h> 
#include "../Logging/GameDebugDraw.h"
#include "Camera.h"
#include "MCIPlayer.h"
#include "../HUD/HUD.h"
#include "../Scence/Scence1.h"
#include "../Scence/Scence2.h"
#include "../Scence/Scence3.h"

World *World::_instance = NULL;

World::World()
{

}

World::~World()
{
	if (scence) {
		delete scence;
	}
}

void World::SetScence(Scence* s) {
	if (this->scence) {
		delete this->scence;
		this->scence = nullptr;
	}
	this->scence = s;
}

void World::ReplaceScence(SCENCE scenceType) {
	switch (scenceType) {
		case SCENCE::SCENCE_1:
			SetScence(new Scence1());
			MCIPlayer::GetInstance()->SwitchSoundTrack(SOUND_TRACK_MAP1, 200 , 38000);
			break;
		case SCENCE::SCENCE_2:
			SetScence(new Scence2());
			MCIPlayer::GetInstance()->SwitchSoundTrack(SOUND_TRACK_MAP2, 200, 143000);
			break;
		case SCENCE::SCENCE_3:
			SetScence(new Scence3());
			MCIPlayer::GetInstance()->SwitchSoundTrack(SOUND_TRACK_MAP3, 200, 143000);
			break;
		default:
			break;
	}
	Camera::GetInstance()->setPosition({ 0,0 });
}

void World::LoadResource()
{
	Texture *texture = Texture::GetInstance();
	//main player
	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN, D3DCOLOR_XRGB(255, 163, 177));
	//enemy
	texture->Add(ID_TEXTURE_MAP_1_ENEMY, PATH_TEXTURE_MAP_1_ENEMY, D3DCOLOR_XRGB(255, 163, 177));
	//enemy die, fire
	texture->Add(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE, PATH_TEXTURE_MAP_1_ENEMY_DIE_FIRE, D3DCOLOR_XRGB(255, 163, 177));
	//health
	texture->Add(HEALTH_ID, HEALTH, D3DCOLOR_XRGB(0, 0, 0));
	//Box
	texture->Add(BOX_ID, BOX, D3DCOLOR_XRGB(0, 0, 0));
	//Point
	texture->Add(POINT_ID, POINT_BOX, D3DCOLOR_XRGB(0, 0, 0));
	//Big Shuriken
	texture->Add(BIG_SHURIKEN_ID, PATH_BIG_SHURIKEN, D3DCOLOR_XRGB(0, 128, 128));
	MCIPlayer *mciPlayer = MCIPlayer::GetInstance();
	mciPlayer->Load(SOUND_TRACK_PATH_MAP_1, SOUND_TRACK_MAP1);
	mciPlayer->Load(SOUND_TRACK_PATH_MAP_2, SOUND_TRACK_MAP2);
	mciPlayer->Load(SOUND_TRACK_PATH_MAP_3, SOUND_TRACK_MAP3);
	mciPlayer->Load(SOUND_PATH_EFFECT_ATK, SOUND_ATK);
	mciPlayer->Load(SOUND_PATH_EFFECT_ATK_SMALL_SHURIKEN, SOUND_ATK_SMALL_SHURIKEN);
	mciPlayer->Load(SOUND_PATH_EFFECT_ATK_BIG_SHURIKEN, SOUND_ATK_BIG_SHURIKEN);
	mciPlayer->Load(SOUND_PATH_EFFECT_ATK_FIRE, SOUND_ATK_FIRE);
	mciPlayer->Load(SOUND_PATH_EFFECT_JUMP, SOUND_JUMP);
	mciPlayer->Load(SOUND_PATH_EFFECT_WOUNDED, SOUND_WOUNDED);
	mciPlayer->Load(SOUND_PATH_EFFECT_DIGEST_FOOD, SOUND_DIGEST_FOOD);
	mciPlayer->Load(SOUND_PATH_EFFECT_ENEMY_DIE, SOUND_ENEMY_DIE);
	mciPlayer->Load(SOUND_PATH_EFFECT_ENEMY_GUN, SOUND_ENEMY_GUN);
	mciPlayer->Load(SOUND_PATH_EFFECT_ENEMY_BAZOKA, SOUND_ENEMY_BAZOKA);
	mciPlayer->Load(SOUND_PATH_EFFECT_BOSS_EXPLOSION, SOUND_BOSS_EXPLOSION);
	mciPlayer->Load(SOUND_PATH_EFFECT_BOSS_JUMP, SOUND_BOSS_JUMP);
	Player *main = Player::GetInstance();
	Camera* camera = Camera::GetInstance();
	HUD* hud = HUD::GetInstance();
	ReplaceScence(SCENCE::SCENCE_1);
}

void World::Update(float deltaTime)
{
	if (Player::GetInstance()->GetAlphaEndPoint() == 0) {
		switch (scence->GetScenceType()) {
		case SCENCE::SCENCE_1:
			this->ReplaceScence(SCENCE::SCENCE_2);
			break;
		case SCENCE::SCENCE_2:
			this->ReplaceScence(SCENCE::SCENCE_3);
			break;
		default:
			break;
		}
		return;
	}
	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE && scence->GetScenceType() == SCENCE::SCENCE_3) {
		ReplaceScence(SCENCE::SCENCE_2);
		return;
	}
	scence->Update(deltaTime);
	
}

void World::Render()
{
	scence->Render();
}
