#include "World.h"
#include "GameDebugDraw.h"
#include "Camera.h"
#include "Sound.h"
#include "Text.h"
#include "Scence2.h"
#include "Scence3.h"
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
			break;
		case SCENCE::SCENCE_2:
			SetScence(new Scence2());
			break;
		case SCENCE::SCENCE_3:
			SetScence(new Scence3());
			break;
		default:
			break;
	}
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
	Sound* sound = Sound::GetInstance();
	sound->LoadSound(SOUND_PATH_EFFECT_ATK, SOUND_ATK);
	sound->LoadSound(SOUND_PATH_EFFECT_ATK_SMALL_SHURIKEN, SOUND_ATK_SMALL_SHURIKEN);
	sound->LoadSound(SOUND_PATH_EFFECT_ATK_BIG_SHURIKEN, SOUND_ATK_BIG_SHURIKEN);
	sound->LoadSound(SOUND_PATH_EFFECT_ATK_FIRE, SOUND_ATK_FIRE);
	sound->LoadSound(SOUND_PATH_EFFECT_JUMP, SOUND_JUMP);
	sound->LoadSound(SOUND_PATH_EFFECT_WOUNDED, SOUND_WOUNDED);
	sound->LoadSound(SOUND_PATH_EFFECT_DIGEST_FOOD, SOUND_DIGEST_FOOD);
	sound->LoadSound(SOUND_PATH_EFFECT_ENEMY_DIE, SOUND_ENEMY_DIE);
	sound->LoadSound(SOUND_PATH_EFFECT_ENEMY_GUN, SOUND_ENEMY_GUN);
	sound->LoadSound(SOUND_PATH_EFFECT_ENEMY_BAZOKA, SOUND_ENEMY_BAZOKA);
	sound->LoadSound(SOUND_PATH_EFFECT_BOSS_JUMP, SOUND_BOSS_JUMP);
	Player *main = Player::GetInstance();
	Text* text = Text::GetInstance();
	Camera* camera = Camera::GetInstance();
	HUD* hud = HUD::GetInstance();
	ReplaceScence(SCENCE::SCENCE_1);
}

void World::Update(float deltaTime)
{
	if (Player::GetInstance()->GetAlphaEndPoint() == 0) {
		switch (scence->GetScenceType()) {
		case SCENCE::SCENCE_1:
			SetScence(new Scence2());
			break;
		case SCENCE::SCENCE_2:
			SetScence(new Scence3());
			break;
		default:
			break;
		}
		return;
	}
	scence->Update(deltaTime);
}

void World::Render()
{
	scence->Render();
	Game::GetInstance()->Draw(0, 0, 0, 0, 256, 208, D3DCOLOR_ARGB(50, 60, 70, 80));
}
