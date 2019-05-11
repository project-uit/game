#include "Katana.h"

Katana::Katana() {

}

Katana::~Katana() {

}

RECT Katana::GetBoundingBox() {
	return boundingBox;
}

void Katana::SetBoundingBox(RECT r) {
	boundingBox = r;
}

void Katana::Reset() {
	RECT rect;
	rect.left = 0;
	rect.right = 0;
	rect.top = 0;
	rect.bottom = 0;
	boundingBox = rect;
}