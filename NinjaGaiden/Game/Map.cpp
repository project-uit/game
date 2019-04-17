#include "Map.h"
Map::Map()
{

}

Map::Map(int tileWidth, int tileHeight, int numOfColumn, int numOfRow) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->numOfColumn = numOfColumn;
	this->numOfRow = numOfRow;
}

void Map::LoadMap(LPCWSTR filePath, LPCWSTR tileset, int ID_MAP)
{
	fstream fs(filePath);
	fs >> numOfRow >> numOfColumn >> tileWidth >> tileHeight;

	this->list = new vector<vector<int>*>();

	for (int i = 0; i < numOfRow; i++) {

		vector<int>* temp = new vector<int>();
		for (int j = 0; j < numOfColumn; j++) {
			int tempNumber;
			fs >> tempNumber;
			temp->push_back(tempNumber);
			if (i == 0) {
				this->width += tileWidth;
			}
		}
		this->list->push_back(temp);
		this->height += tileHeight;
	}
	DebugOut((wchar_t *)L"[Map.cpp] Width X Height map: %d %d\n", width, height);
	fs.close();

	Texture::GetInstance()->Add(ID_MAP, tileset);
	this->texture = Texture::GetInstance()->Get(ID_MAP);
}

Map::~Map()
{
	for (int i = 0; i < this->list->size(); i++) {
		delete this->list->at(i);
	}
	delete this->list;
}

bool Map::isRectOverlap(RECT r1, RECT r2) {
	if (r1.left > r2.right || r1.right < r2.left || r1.top > r2.bottom || r1.bottom < r2.top)
	{
		return false;
	}
	return true;
}

void Map::drawMap()
{
	int tileMapWidth = 0;
	for (int i = 0; i < this->list->size(); i++) {
		for (int j = 0; j < this->list->at(i)->size(); j++) {
			int number = this->list->at(i)->at(j);
			D3DXVECTOR3 position(j * this->tileHeight, i * this->tileWidth, 0);
			//lấy tọa độ vẽ tile
			RECT tile;
			tile.left = position.x;
			tile.top = position.y;
			tile.bottom = tile.top + this->tileHeight;
			tile.right = tile.left + this->tileWidth;
			if (number != 0 && isRectOverlap(tile, Camera::GetInstance()->getRECT())) {
			/*	Game::GetInstance()->Draw(j * this->tileHeight + this->tileHeight / 2, i * this->tileWidth + this->tileWidth / 2
					, this->texture, (number - 1) * 16, 0, number * 16, 16);*/
				Game::GetInstance()->Draw(position.x, position.y, this->texture, (number - 1) * 16, 0, number*16, 16);
			}

		}
	}
}