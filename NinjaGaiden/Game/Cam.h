#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Cam
{
public:
	Cam(int width, int height);

	//center of Cam
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	~Cam();

private:
	int             mWidth,
		mHeight;

	D3DXVECTOR3     mPosition;
};

