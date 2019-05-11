#include "World.h"
#include "GameDebugDraw.h"
#include "Camera.h"
#include "Sound.h"
#include "Text.h"
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
			break;
		case SCENCE::SCENCE_3:
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
	Sound* sound = Sound::GetInstance();
	Player *main = Player::GetInstance();
	Text* text = Text::GetInstance();
	Camera* camera = Camera::GetInstance();
	ReplaceScence(SCENCE::SCENCE_1);
}

void World::Update(float deltaTime)
{
	scence->Update(deltaTime);
}

void World::Render()
{
	/*Text::GetInstance()->DrawString("SCORE - 000000 STAGE - 1 - 1", 0, 0, 200, 30);
	Text::GetInstance()->DrawString("TIMER - 000 ", 0, 16, 50, 30);
	Text::GetInstance()->DrawString("P - 01", 0, 32, 50, 30);*/
	scence->Render();
}
