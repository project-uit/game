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
	map = new Map(16, 16, 128, 11);
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Player *main = Player::GetInstance();
	item = new Item();
	this->objects = new vector<Object*>();
	this->objects->push_back(item);
}

void World::Update(float deltaTime)
{
	Player::GetInstance()->Update(deltaTime, this->objects);
	item->Update(deltaTime);
}

void World::Render()
{
	
	map->drawMap();
	item->Render();
	Player::GetInstance()->Render();

}
