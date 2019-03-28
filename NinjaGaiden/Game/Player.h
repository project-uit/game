#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"

#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

class Player : public Object
{
private:

	static Player* _instance;
	PLAYER_STATE state;
	Sprite* standSprite;
	Sprite* runSprite;

public:
	Player();
	~Player();


	PLAYER_STATE GetState();
	void SetState(PLAYER_STATE value);

	void ResetAllSprites();
	bool GetStateActive();

	void Reset(float  x, float y);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();

	static Player* GetInstance() {
		if (_instance == NULL) _instance = new Player();
		return _instance;
	}
};

