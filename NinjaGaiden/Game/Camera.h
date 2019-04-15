#pragma once
#include <DirectXMath.h>
#include <d3dx9.h>
#include "Constants.h"
class Camera
{
private:
	static Camera* _instance;
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
	//update lại vị trí camera
	void Update(int x, int y, int WidthMap, int G_ScreenWidth);
	//Thực hiện phép dời hình
	void SetTransForm(LPDIRECT3DDEVICE9);
	RECT getRECT();
	~Camera();
	static void SetInstance(int width, int height, float angle, D3DXVECTOR3 scaleFactors) {
		if (_instance == NULL) {
			_instance = new Camera(width, height, angle, scaleFactors);
		}
	}
	static Camera* GetInstance() {
		return _instance;
	}


};
