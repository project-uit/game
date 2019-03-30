#pragma once
#include <windef.h>
class Boundary : public RECT {

public:
	Boundary(RECT rect);
	Boundary();
	~Boundary();
	RECT GetRECT();
	void SetRECT(RECT rect);
	LONG GetWitdh();
	LONG GetHeight();
};
