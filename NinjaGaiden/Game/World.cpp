#include "World.h"

World *World::_instance = NULL;

World::World()
{

}

World::~World()
{
}

void World::LoadResource()
{
	Texture *texture = Texture::GetInstance();
	
	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN, D3DCOLOR_XRGB(255, 163, 177));
	texture->Add(ID_TEXTURE_MAP_1, PATH_TEXTURE_MAP_1);


	Player *main = Player::GetInstance();
	item = new Item();
	this->objects = new vector<Object*>();
	this->objects->push_back(item);
	DebugOut((wchar_t *)L"[Resource] Loading resource successfully\n");

	
}

void World::Update(float deltaTime)
{
	Player::GetInstance()->Update(deltaTime, this->objects);
	item->Update(deltaTime);
}

void World::Render()
{
	Game::GetInstance()->Draw(0, 0, Texture::GetInstance()->Get(ID_TEXTURE_MAP_1), 0, 0, 600, 600);
	item->Render();
	Player::GetInstance()->Render();
	
}
