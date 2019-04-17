#include "Camera.h"
#include "Debug.h"
Camera* Camera::_instance = NULL;
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
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-cameraX, -cameraY, 0, 1
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
