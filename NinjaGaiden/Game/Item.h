#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include <map>
#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

class Item : public Object
{
private:
	Sprite* sprite;
public:
	Item();
	~Item();
	void Update(float t);
	void Render();
};

