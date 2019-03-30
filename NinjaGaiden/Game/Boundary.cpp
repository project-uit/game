#include "Boundary.h"

Boundary::Boundary(RECT rect) {
	this->top = rect.top;
	this->left = rect.left;
	this->right = rect.right;
	this->bottom = rect.bottom;
}

Boundary::Boundary() {
	this->top = this->left = this->bottom = this->right = 0.0f;
}

Boundary::~Boundary() {

}

RECT Boundary::GetRECT() {
	return *this;
}

void Boundary::SetRECT(RECT rect) {
	*this = rect;
}

LONG Boundary::GetWitdh() {
	return this->left + this->right;
}

LONG Boundary::GetHeight() {
	return this->top + this->bottom;
}