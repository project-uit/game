#include "HUD.h"
#include "Player.h"

HUD* HUD::_instance = NULL;
HUD::HUD() {
	healthPlayer = new Sprite(Texture::GetInstance()->Get(HEALTH_ID), L"sprite\\HUD\\health.txt", 2, 0.0f, 0.5f);
	healthBoss = new Sprite(Texture::GetInstance()->Get(HEALTH_ID), L"sprite\\HUD\\health.txt", 2, 0.0f, 0.5f);
	box = new Sprite(Texture::GetInstance()->Get(BOX_ID), L"sprite\\HUD\\box.txt", 1, 0.0f, 0.4f);
	lifePoint = new Sprite(Texture::GetInstance()->Get(POINT_ID), L"sprite\\HUD\\point.txt", 2, 0.0f, 0.475f);
	//item = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), L"", 2, 0.0f);
}

HUD::~HUD() {
	delete healthBoss;
	delete healthPlayer;
	delete box;
	delete item;
}

void HUD::Update(float t) {
	//healthBoss->SetIndex(0);
}

void HUD::Render(int hpBoss) {
	
	box->DrawSprite(D3DXVECTOR3(67.0f, 3.0f, 0.0f), false);
	for (int i = 0; i < 16; i++) {
		if (i < Player::GetInstance()->GetHp()) {
			healthPlayer->SetIndex(0);
		}
		else {
			healthPlayer->SetIndex(1);
		}
		if (i < hpBoss) {
			healthBoss->SetIndex(0);
		}
		else {
			healthBoss->SetIndex(1);
		}
		float temp = 155 + i * 5;
		healthPlayer->DrawSprite(D3DXVECTOR3(temp, 6.0f, 0.0f), false);
		healthBoss->DrawSprite(D3DXVECTOR3(temp, 16.0f, 0.0f), false);
	}
	lifePoint->DrawSprite(D3DXVECTOR3(57.0f, 16.0f, 0.0f), false);
}