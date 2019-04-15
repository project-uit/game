#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <fstream>
#include "Sprite.h"
#include "Texture.h"
#include "Constants.h"
#include "Game.h"
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

	//void SetWidth(int width);
	//int GetWidth();

	//void SetHeight(int height);
	//int GetHeight();

	//void SetNumOfColumn(int numOfColumn);
	//int GetNumOfColumn();

	//void SetNumOfColumnTileSet(int numOfColumnTileSet);
	//int GetNumOfColumnTileSet();
};