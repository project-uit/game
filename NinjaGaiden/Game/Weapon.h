#pragma once
#include "Object.h"
#include "Sprite.h"
class Weapon : public Object {
protected:
	int point;
	Sprite* sprite;
public:
	Weapon() { }
	~Weapon() {
		delete sprite;
	}
	int GetPoint() { return point; }
};