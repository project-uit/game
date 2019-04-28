#include "Camera.h"
#include "Graphic.h"
Camera* Camera::_instance = NULL;

Camera::Camera()
{
	cameraPosition = { 0,0 };
	worldBoundary = 0;
}

Camera::~Camera()
{

}

D3DXVECTOR3 Camera::transformObjectPosition(D3DXVECTOR3 objectPosition)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = 1.0;
	mt._41 = -this->cameraPosition.x;
	mt._42 = -this->cameraPosition.y;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &objectPosition, &mt);
	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
}

void Camera::Update(D3DXVECTOR3 simonPosition)
{
	cameraPosition = { simonPosition.x - Graphic::GetInstance()->GetWidth() / 2,cameraPosition.y };
	if (cameraPosition.x < 0)
		cameraPosition = { 0 ,cameraPosition.y };
	if (cameraPosition.x + Graphic::GetInstance()->GetWidth() > worldBoundary)
		cameraPosition = { worldBoundary - Graphic::GetInstance()->GetWidth() ,cameraPosition.y };

}
