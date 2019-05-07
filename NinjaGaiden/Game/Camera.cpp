#include "Camera.h"
#include "Graphic.h"
#include "Debug.h"
Camera* Camera::_instance = NULL;

Camera::Camera()
{
	cameraPosition = { 0,0 };
	RECTPosition = { 0, 0 };
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

void Camera::Update(D3DXVECTOR3 playerPosition)
{
	cameraPosition = { playerPosition.x - Graphic::GetInstance()->GetWidth() / 2 + 50, cameraPosition.y };
	RECTPosition = { playerPosition.x, playerPosition.y };
	
	if (cameraPosition.x < 0) {
		cameraPosition = { 0 ,cameraPosition.y };
	}

	if (cameraPosition.x + Graphic::GetInstance()->GetWidth() > worldBoundary) {
		cameraPosition = { worldBoundary - Graphic::GetInstance()->GetWidth() ,cameraPosition.y };
	}
}

RECT Camera::GetRECT() {
	RECT r;
	int width = 290;
	int height = Graphic::GetInstance()->GetHeight();
	SetRect(&r, cameraPosition.x, cameraPosition.y, cameraPosition.x + width, cameraPosition.y + height);
	return r;
}