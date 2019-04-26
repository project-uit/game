#include "World.h"
#include "GameDebugDraw.h"
#include "Camera.h"
#include "Sound.h"
#include "Text.h"
World *World::_instance = NULL;
GameDebugDraw* draw;

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
	this->scence = s;
}

void World::LoadResource()
{
	Texture *texture = Texture::GetInstance();
	//main player
	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN, D3DCOLOR_XRGB(255, 163, 177));
	//enemy
	texture->Add(ID_TEXTURE_MAP_1_ENEMY, PATH_TEXTURE_MAP_1_ENEMY, D3DCOLOR_XRGB(255, 163, 177));
	scence = new Scence1();
	Sound* sound = Sound::GetInstance();
	Player *main = Player::GetInstance();
	draw = new GameDebugDraw();
	Text* text = Text::GetInstance();
}

void World::Update(float deltaTime)
{
	scence->Update(deltaTime);
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition());
}

void World::Render()
{
	Text::GetInstance()->DrawString("SCORE - 000000 STAGE - 1 - 1", 0, 0, 200, 30);
	Text::GetInstance()->DrawString("TIMER - 000 ", 0, 16, 50, 30);
	Text::GetInstance()->DrawString("P - 01", 0, 32, 50, 30);
	scence->Render();
	Player::GetInstance()->Render();
	draw->DrawRect(Player::GetInstance()->GetBoundingBox(), Camera::GetInstance());
}
