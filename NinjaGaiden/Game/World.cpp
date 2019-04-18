﻿#include "World.h"
#include "GameDebugDraw.h"
#include "Camera1.h"
World *World::_instance = NULL;
GameDebugDraw* draw;

World::World()
{

}

World::~World()
{

}

void World::LoadResource()
{
	Texture *texture = Texture::GetInstance();
	//main player
	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN, D3DCOLOR_XRGB(255, 163, 177));
	//enemy
	texture->Add(ID_TEXTURE_MAP_1_ENEMY, PATH_TEXTURE_MAP_1_ENEMY, D3DCOLOR_XRGB(255, 163, 177));
	//map
	map = new Map();
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Player *main = Player::GetInstance();
	item = new Item();
	this->objects = new vector<Object*>();
	this->objects->push_back(item);
	draw = new GameDebugDraw();
	Camera1::GetInstance()->setWorldBoundary(2048);
	Camera1::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
}

void World::Update(float deltaTime)
{
	Player::GetInstance()->Update(deltaTime, this->objects);
	item->Update(deltaTime);
	Camera1::GetInstance()->Update(Player::GetInstance()->GetPosition());
}

void World::Render()
{
	map->drawMap();
	item->Render();
	Player::GetInstance()->Render();
	draw->DrawRect(item->GetBoundingBox(), nullptr);
	draw->DrawRect(Player::GetInstance()->GetBoundingBox(), nullptr);
}
