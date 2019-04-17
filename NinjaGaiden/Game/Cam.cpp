#include "Cam.h"


Cam::Cam(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(0, 0, 0);
}


Cam::~Cam()
{

}

void Cam::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Cam::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
}

D3DXVECTOR3 Cam::GetPosition()
{
	return mPosition;
}

RECT Cam::GetBound()
{
	RECT bound;

	bound.left = mPosition.x - mWidth / 2;
	bound.right = bound.left + mWidth;;
	bound.top = mPosition.y - mHeight / 2;
	bound.bottom = bound.top + mHeight;

	return bound;
}

int Cam::GetWidth()
{
	return mWidth;
}

int Cam::GetHeight()
{
	return mHeight;
}