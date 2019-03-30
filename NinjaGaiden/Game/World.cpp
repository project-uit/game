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

	this->testSpriteStand = new Sprite(texture->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 17, 32);

	Player *main = Player::GetInstance();
	DebugOut((wchar_t *)L"[Resource] Loading resource successfully\n");
}

void World::Update(float deltaTime)
{
	Player::GetInstance()->Update(deltaTime, new vector<Object*>);
}

void World::Render()
{
	Game::GetInstance()->Draw(0, 0, Texture::GetInstance()->Get(ID_TEXTURE_MAP_1), 0, 0, 600, 600);
	Player::GetInstance()->Render();
}
