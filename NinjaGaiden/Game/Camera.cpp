#include "Camera.h"

Camera::Camera(int width, int height, float _angle, D3DXVECTOR3 _scaleFactors)
{
	Width = width;
	Height = height;
	angle = _angle;
	scaleFactors = _scaleFactors;

	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::Camera()
{
	angle = 0;
	Width = 0;
	Height = 0;
	cameraX = 0;
	cameraY = 0;
}

void Camera::Update(int x, int y, int WidthMap, int G_ScreenWidth)
{
	cameraX = x;
	cameraY = y;
	if (cameraX < G_ScreenWidth / 2) {
		cameraX = G_ScreenWidth / 2;
	}

	if (cameraX > WidthMap - G_ScreenWidth / 2) {
		cameraX = WidthMap - G_ScreenWidth / 2;
	}
		
	this->viewMatrix = D3DXMATRIX(
		scaleFactors.x * cos(angle), scaleFactors.x * sin(angle), 0, 0,
		-scaleFactors.y * sin(angle), scaleFactors.y * cos(angle), 0, 0,
		0, 0, scaleFactors.z, 0,
		-cameraX * scaleFactors.x * cos(angle) + cameraY * scaleFactors.y * sin(angle),
		-cameraX * scaleFactors.y * sin(angle) - cameraY * scaleFactors.y * cos(angle), 0, 1
	);
}

void Camera::SetTransForm(LPDIRECT3DDEVICE9 G_d3ddv)
{
	G_d3ddv->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	G_d3ddv->SetTransform(D3DTS_WORLD, &identityMatrix);
	G_d3ddv->SetTransform(D3DTS_VIEW, &viewMatrix);
}

RECT Camera::getRECT()
{
	RECT result;
	result.left = cameraX - Width / 2 - 90;
	result.right = cameraX + Width / 2;
	result.top = cameraY - Height / 2;
	result.bottom = cameraY + Height / 2;
	return result;
}

Camera::~Camera()
{
}
