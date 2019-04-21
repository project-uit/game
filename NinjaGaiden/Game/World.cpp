#include "World.h"
#include "GameDebugDraw.h"
#include "Camera.h"
#include "Text.h"
World *World::_instance = NULL;
GameDebugDraw* draw;
Square* square;
World::World()
{

}

World::~World()
{

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
	Player *main = Player::GetInstance();
	item = new Item();
	this->objects = new vector<Object*>();
	square = new Square(48, 192, 528+16, 224);
	this->objects->push_back(item);
	this->objects->push_back(square);
	draw = new GameDebugDraw();
	scence->GetObjects()->push_back(square);
	Text::GetInstance();
}

void World::Update(float deltaTime)
{
	Player::GetInstance()->Update(deltaTime, this->objects);
	square->Update(deltaTime);
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
	draw->DrawRect(item->GetBoundingBox(), Camera::GetInstance());
	draw->DrawRect(Player::GetInstance()->GetBoundingBox(), Camera::GetInstance());
	draw->DrawRect(square->GetBoundingBox(), Camera::GetInstance());
}
