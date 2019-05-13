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
	//health
	texture->Add(HEALTH_ID, HEALTH, D3DCOLOR_XRGB(0, 0, 0));
	//Box
	texture->Add(BOX_ID, BOX, D3DCOLOR_XRGB(0, 0, 0));
	//Point
	texture->Add(POINT_ID, POINT_BOX, D3DCOLOR_XRGB(0, 0, 0));
	
	Sound* sound = Sound::GetInstance();
	Player *main = Player::GetInstance();
	Text* text = Text::GetInstance();
	Camera* camera = Camera::GetInstance();
	HUD* hud = HUD::GetInstance();
	ReplaceScence(SCENCE::SCENCE_1);
}

void World::Update(float deltaTime)
{
	scence->Update(deltaTime);
}

void World::Render()
{
	scence->Render();
}
