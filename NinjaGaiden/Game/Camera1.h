#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"

class Camera1
{
	static Camera1 * _instance;

	D3DXVECTOR2 cameraPosition;

	float worldBoundary;
public:
	Camera1();

	void Update(D3DXVECTOR3 simonPosition);
	D3DXVECTOR3 transformObjectPosition(D3DXVECTOR3 objectPosition);

	D3DXVECTOR2 getPosition() { return cameraPosition; }
	void setPosition(D3DXVECTOR2 a) { this->cameraPosition = a; }
	RECT GetRECT();
	~Camera1();

	static Camera1* GetInstance() {
		if (_instance == NULL) _instance = new Camera1();
		return _instance;
	}

	void setWorldBoundary(float a) { this->worldBoundary = a; }
};