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
		}
		this->list->push_back(temp);
	}

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

void Map::drawMap()
{
	for (int i = 0; i < this->list->size(); i++) {
		for (int j = 0; j < this->list->at(i)->size(); j++) {
			int number = this->list->at(i)->at(j);
			if (number != 0) {
				Game::GetInstance()->Draw(j * 16, i * 16, this->texture, (number - 1) * 16, 0, number*16, 16);
			}
		}
	}
}