#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <fstream>
#include "Sprite.h"
#include "Texture.h"
#include "Constants.h"
#include "Game.h"
#include "Camera.h"
class Map
{
private:
	LPDIRECT3DTEXTURE9 texture;
	vector<vector<int>*>* list;
	int width;
	int height;

	int tileWidth;
	int tileHeight;

	int numOfColumn;
	int numOfRow;

	int numOfColumnTileSet;
	int numOfRowTileSet;

public:
	Map();
	Map(int tileWidth, int tileHeight, int numOfColumn, int numOfRow);
	
	~Map();
	void LoadMap(LPCWSTR filePath, LPCWSTR tileset, int ID_MAP);
	void drawMap();

	void SetWidth(int width) {
		this->width = width;
	}
	int GetWidth() {
		return this->width;
	}

	void SetHeight(int height) {
		this->height = height;
	}
	int GetHeight() {
		return this->height;
	}

	//void SetNumOfColumn(int numOfColumn);
	//int GetNumOfColumn();

	//void SetNumOfColumnTileSet(int numOfColumnTileSet);
	//int GetNumOfColumnTileSet();
};