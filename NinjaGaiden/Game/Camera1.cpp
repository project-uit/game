#include "Camera1.h"

Camera1* Camera1::_instance = NULL;

Camera1::Camera1()
{
	cameraPosition = { 0,0 };
	worldBoundary = 0;
}


Camera1::~Camera1()
{
}

D3DXVECTOR3 Camera1::transformObjectPosition(D3DXVECTOR3 objectPosition)
{
	/*D3DXVECTOR3 value = { objectPosition.x - Camera1Position.x,objectPosition.y - Camera1Position.y,0 };
	return value;*/

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);

	mt._22 = 1.0;
	mt._41 = -this->cameraPosition.x;
	mt._42 = -this->cameraPosition.y;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &objectPosition, &mt);
	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
}

void Camera1::Update(D3DXVECTOR3 simonPosition)
{
	cameraPosition = { simonPosition.x - 320 / 2,cameraPosition.y };
	if (cameraPosition.x < 0)
		cameraPosition = { 0 ,cameraPosition.y };
	if (cameraPosition.x + 320 > worldBoundary)
		cameraPosition = { worldBoundary - 320,cameraPosition.y };

}
