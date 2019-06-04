#pragma once
#include "../../Framework/Object.h"
#include "../../Framework/Sprite.h"
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