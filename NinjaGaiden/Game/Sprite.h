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
	vector<RECT>* boundingBox;
	int width;
	int height;
	int count;
	int index;
	float rotate;
	float scale;
	void SetSpritePositions(LPCWSTR filePath);
	bool isComplete;
	DWORD time;
	DWORD lastFrameTime;
public:
	Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, int count, int width, int height, float scale = 1.0f);
	Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, int count, float scale = 1.0f);
	Sprite(LPDIRECT3DTEXTURE9 texture, int index, int count, int width, int height);
	~Sprite();
	void SetIndex(int index);
	int GetIndex();
	void NextSprite();
	bool GetIsComplete() {
		return isComplete;
	}
	void setIsComplete(bool complete) {
		this->isComplete = complete;
	}
	//Vẽ sprite bên phải ko bị lệch
	void DrawSprite(D3DXVECTOR3 position, bool flagRight);
	//Vẽ sprite bên trái bị lệch
	void DrawSprite(D3DXVECTOR3 position, bool flagRight, int x, int y);
	//Đọc tọa độ ảnh
	RECT ReadCurrentSpritePosition();
	RECT GetBoudingBoxFromCurrentSprite();
	RECT GetBoudingBoxFromCurrentSprite(DIRECTION direct);
	RECT GetRectDrawSprite();
	DWORD GetTime() { return time; }
	void Reset();
	void SetScale(float scale);
	int GetCount();
	int GetWidth();
	int GetHeight();
};

