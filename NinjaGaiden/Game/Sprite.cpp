#include  "Sprite.h"
#include "Debug.h"
Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, int count, int width, int height, float scale)
{

	if (texture == NULL)
		return;
	this->texture = texture;
	this->count = count;
	this->width = width;
	this->height = height;
	this->scale = scale;
	this->index = 0;

	this->spritePositions = new vector<vector<int>*>();

	this->SetSpritePositions(filePath);
}

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, int count, float t, float scale)
{
	if (texture == NULL) {
		return;
	}
	this->count = count;
	this->texture = texture;
	this->index = 0;
	this->scale = scale;
	this->spritePositions = new vector<vector<int>*>();
	this->timePerFrame = t;
	this->SetSpritePositions(filePath);
	this->width = this->spritePositions->at(this->index)->at(2);
	this->height = this->spritePositions->at(this->index)->at(3);
}

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, int index, int count, int width, int height)
{
	if (texture == NULL)
		return;
	this->texture = texture;
	this->count = count;
	this->width = width;
	this->height = height;

	this->index = 0;

	this->spritePositions = new vector<vector<int>*>();

	vector<int> * positions = new vector<int>();
	positions->push_back((index - 1) * 32);
	positions->push_back(0);
	this->spritePositions->push_back(positions);
}

Sprite::~Sprite()
{
	for (int i = 0; i < this->spritePositions->size(); i++) {
		delete this->spritePositions->at(i);
	}
	spritePositions->clear();
	delete this->spritePositions;
}

void Sprite::SetSpritePositions(LPCWSTR filePath)
{
	// Đọc thông tin file
	fstream f;
	try
	{
		f.open(filePath);
	}
	catch (fstream::failure e)
	{
		trace(L"Error when Init Sprite %s", filePath);
		return;
	}

	string line;
	while (!f.eof()) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> * tempVector = new vector<int>();

		while (getline(iss, splitString, '\t'))
		{
			tempVector->push_back(stoi(splitString));
		}
		this->spritePositions->push_back(tempVector);
		//DebugOut((wchar_t *)L"Thông số %d\n", stoi(splitString));
	}

	trace(L"Done Init Sprite %s", filePath);
	f.close();
}

void Sprite::NextSprite()
{
	DWORD now = GetTickCount();
	DWORD t = this->GetTime();
	if (now - lastFrameTime >= timePerFrame)
	{
		lastFrameTime = now;
		this->index = (this->index + this->count) % this->count + 1;
		if (this->index == count) {
			isComplete = true;
			this->index = 0;
		}
	}
}

void Sprite::DrawSprite(D3DXVECTOR3 position, bool flagRight)
{
	if (this->texture == NULL)
		return;
	RECT rect = ReadCurrentSpritePosition();	//đọc tọa độ của sprite trong file txt

	D3DXVECTOR3 spriteCentre = D3DXVECTOR3((float)width, (float)height, 0);

	D3DXMATRIX mat;
	float tempTurnRight = 1.0f;
	if (!flagRight) {
		tempTurnRight = -1.0f;
	}
	directionX = tempTurnRight * this->scale;
	D3DXVECTOR3 scaling(tempTurnRight * this->scale, this->scale, 1.0f);
	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation(&mat, &D3DXVECTOR3(this->width / 2, this->height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);
	Game::GetInstance()->GetSpriteHandler()->SetTransform(&mat);
	Game::GetInstance()->GetSpriteHandler()->Draw(this->texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::DrawSprite(D3DXVECTOR3 position, bool flagRight, int x, int y)
{
	if (this->texture == NULL)
		return;
	RECT rect = ReadCurrentSpritePosition();	//đọc tọa độ của sprite trong file txt

	// Texture being used is width by height:
	D3DXVECTOR3 spriteCentre = D3DXVECTOR3((float)this->width, (float)this->height, 0);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// Biến này làm cho object quay theo trục X (trục dọc)
	float tempTurnRight = 1.0f;

	if (!flagRight) {
		tempTurnRight = -1.0f;
		position.x += x;
		position.y += y;
	}
	directionX = tempTurnRight * this->scale;
	D3DXVECTOR3 scaling(tempTurnRight * this->scale, this->scale, 1.0f);
	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation(&mat, &D3DXVECTOR3(this->width / 2, this->height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);
	//D3DXMatrixRotationX(&mat, 3.14f);
	Game::GetInstance()->GetSpriteHandler()->SetTransform(&mat);
	Game::GetInstance()->GetSpriteHandler()->Draw(this->texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

RECT Sprite::ReadCurrentSpritePosition()
{
	RECT rect;
	vector<int>* tempVector = this->spritePositions->at(this->index);
	rect.left = tempVector->at(0);
	rect.top = tempVector->at(1);
	this->width = tempVector->at(2);
	this->height = tempVector->at(3);
	rect.right = rect.left + this->width;
	rect.bottom = rect.top + this->height;
	return rect;
}

RECT Sprite::GetBoudingBoxFromCurrentSprite()
{
	RECT rect;
	vector<int>* tempVector = this->spritePositions->at(this->index);
	//tempVector->at(4); //x
	//tempVector->at(5); //y
	//rect.left + tempVector->at(6);// width
	//rect.top + tempVector->at(7);//height

	//Nếu hướng phải (mặc định)
	SetRect(&rect, tempVector->at(4), tempVector->at(5),
		tempVector->at(4) + tempVector->at(6), tempVector->at(5) + tempVector->at(7));
	//Nếu hướng trái
	if (directionX < 0) {
		if (tempVector->size() > 8) {
			//Left, top, right, bottom
			DebugOut((wchar_t *)L"Va chạm trục X1!\n");
			rect.left = -tempVector->at(8);
			rect.top = tempVector->at(5);
			rect.right = -tempVector->at(8) + tempVector->at(6);
			rect.bottom = tempVector->at(5) + tempVector->at(7);
		}
	}
	return rect;
}

void Sprite::Reset()
{
	this->index = 0;
	isComplete = false;
}
void Sprite::SetIndex(int idx) {
	this->index = idx;
}

int Sprite::GetIndex() {
	return this->index;
}

int Sprite::GetCount() {
	return this->count;
}

void Sprite::SetScale(float scale) {
	this->scale = scale;
}

int Sprite::GetWidth() {
	return this->width;
}

int Sprite::GetHeight() {
	return this->height;
}