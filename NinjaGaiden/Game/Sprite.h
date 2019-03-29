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
	int count;						  // So luong sprite trong texture
	int index;
	int rotate;
	float scale;
	void SetSpritePositions(LPCWSTR filePath);

public:
	Sprite(LPDIRECT3DTEXTURE9, LPCWSTR, int, int, int);
	Sprite(LPDIRECT3DTEXTURE9, LPCWSTR); // Phương thức mới dùng để khỏi tạo sprite và dựa hoàn toàn vào file
	Sprite(LPDIRECT3DTEXTURE9, int, int, int, int); // Phương thức dùng để khởi tạo sprite đối vs những viên gạch
	~Sprite();
	void SetIndex(int index);
	int GetIndex();
	void NextSprite();
	void DrawSprite(D3DXVECTOR3 position, bool flagRight);	//draw multi sprites
	RECT ReadCurrentSpritePosition();
	RECT ReadCurrentSpritePositionWithBoundingBox();
	void Reset();
	void SetScale(int scale);
	int GetCount() {
		return this->count;
	}
};

