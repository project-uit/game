#include "Scence1.h"
#include "SoldierSword.h"
#include "GameDebugDraw.h"
SoldierSword* soldierSword;
GameDebugDraw* drawScence1;
Square* square;

Scence1::Scence1()
{
	
	this->LoadResource();
}

Scence1::~Scence1()
{

}

void Scence1::LoadResource()
{
	map = new Map();
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	Camera::GetInstance()->setWorldBoundary(2048);
	soldierSword = new SoldierSword();
	drawScence1 = new GameDebugDraw();
	square = new Square(48, 192, 528 + 16, 224);
	Grid::GetInstance(262, map->GetWidth(), false);
	Grid::GetInstance()->Add(soldierSword);
	Grid::GetInstance()->Add(square);
	//this->objects->push_back(Player::GetInstance());

	//this->map = new Map(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);

	//fstream fs(PATH_POS_GROUND_MAP_1);

	//int numberOfGround, left, top, right, bottom;

	//fs >> numberOfGround;

	//for (int i = 0; i < numberOfGround; i++) {
	//	fs >> left >> top >> right >> bottom;

	//	RECT rect;
	//	rect.top = top;
	//	rect.left = left;
	//	rect.right = right;
	//	rect.bottom = bottom;

	//	this->InitHorizontalBrick(rect);
	//}

	//fs.close();

	//for (int i = 0; i < this->bricks->size(); i++) {
	//	RECT rect = this->bricks->at(i);
	//	Square * square = new Square(rect.left, rect.top, rect.right, rect.bottom);
	//	this->objects->push_back(square);
	//}

	//for (int i = 0; i < this->objects->size(); i++) {
	//	Grid::GetInstance()->Add(this->objects->at(i));
	//}
}

void Scence1::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void Scence1::Render()
{
	map->drawMap();
	Scence::Render();
}