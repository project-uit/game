#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Debug.h"
#include <vector>
#include "Game.h"
#include "Constants.h"
using namespace std;
class Sprite
{
private:
	LPDIRECT3DTEXTURE9 texture;      // file chua sprite lon

	vector<vector<int>*> * spritePositions; // Dùng để lưu lại vị trí tất cả các sprite thuộc về Stage đang xét

	int width;
	int height;
	int count;
	int index;
	float rotate;
	float scale;
	void SetSpritePositions(LPCWSTR filePath);

public:
	Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, int count, int width, int height, float scale = 1.0f);
	Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, float scale = 1.0f);
	Sprite(LPDIRECT3DTEXTURE9 texture, int index, int count, int width, int height);
	~Sprite();
	void SetIndex(int index);
	int GetIndex();
	void NextSprite();
	void DrawSprite(D3DXVECTOR3 position, bool flagRight);
	RECT ReadCurrentSpritePosition();
	RECT ReadCurrentSpritePositionWithBoundingBox();
	void Reset();
	void SetScale(float scale);
	int GetCount();
};

