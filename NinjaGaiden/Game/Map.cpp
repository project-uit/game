#include "Map.h"
#include "Camera1.h"
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
	D3DXVECTOR2 camposition = Camera1::GetInstance()->getPosition();

	int top, left, right, bottom;
	int tileMapWidth = 0;
	for (int i = 0; i < 208/tileHeight; i++) {
		for (int j = 0; j < 320/tileWidth; j++) {
			int number = this->list->at(i)->at(j);
			if (number != 0) {
				int a = i + camposition.y / tileWidth;
				int b = j + camposition.x / tileHeight;
				left = ((list->at(a)->at(b) - 1) % 79)*tileWidth;
				top = ((list->at(a)->at(b) - 1) / 79)*tileHeight;
				right = left + tileWidth;
				bottom = top + tileHeight;
				Game::GetInstance()->Draw(
					j*tileWidth - (int)camposition.x % tileWidth, i*tileHeight - (int)camposition.y % tileHeight + 10,
					texture,
					left, top, right, bottom);
			}
		}
	}
}