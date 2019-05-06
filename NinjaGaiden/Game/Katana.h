#pragma once
#include <Windows.h>
#include "Object.h"
class Katana {
private:
	RECT boundingBox;
public:
	Katana();
	~Katana();
	RECT GetBoundingBox();
	void SetBoundingBox(RECT r);
	void Reset();
};