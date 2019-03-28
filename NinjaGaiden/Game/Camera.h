#pragma once
#include <DirectXMath.h>
#include <d3dx9.h>
#include "Constants.h"
class Camera
{
private:
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	D3DXVECTOR3 scaleFactors;
	float angle;
	int Width;
	int Height;
	int cameraX;
	int cameraY;
public:
	Camera(int width, int height, float angle, D3DXVECTOR3 scaleFactors);
	Camera();
	void Update(int x, int y, int WidthMap, int G_ScreenWidth);
	void SetTransForm(LPDIRECT3DDEVICE9);
	RECT getRECT();
	~Camera();
};





