#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"

class Camera
{
	static Camera * _instance;

	D3DXVECTOR2 cameraPosition;
	D3DXVECTOR2 RECTPosition;
	float worldBoundary;
public:
	Camera();

	void Update(D3DXVECTOR3 playerPosition);
	D3DXVECTOR3 transformObjectPosition(D3DXVECTOR3 objectPosition);

	D3DXVECTOR2 getPosition() { return cameraPosition; }
	void setPosition(D3DXVECTOR2 a) { this->cameraPosition = a; }
	RECT GetRECT();
	RECT GetRECTx();
	~Camera();

	static Camera* GetInstance() {
		if (_instance == NULL) _instance = new Camera();
		return _instance;
	}

	void setWorldBoundary(float mapWidth) { this->worldBoundary = mapWidth; }
};