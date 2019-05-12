#include "Scence.h"
#include "Player.h"
#include "Text.h"
#include <iomanip> 
Scence::Scence()
{
	this->map = new Map();
	this->timer = 0;
	this->name = "";
}

Scence::~Scence()
{
	delete map;
}

void Scence::Update(float deltaTime)
{
	Camera::GetInstance()->Update(Player::GetInstance()->GetPosition());
	Grid::GetInstance()->UpdateGrid(Player::GetInstance());
	Grid::GetInstance()->UpdateObject(deltaTime);
	if (time >= 1.0f) {
		this->timer--;
		time = 0;
		if (this->timer <= 0) {
			this->timer = 0;
		}
	}
	else {
		time += deltaTime;
	}
}

void Scence::RenderText() {
	// Đếm thời gian
	std::stringstream timer;
	timer << std::setw(3) << std::setfill('0') << this->timer;
	//Mạng người chơi
	int temp = Player::GetInstance()->GetLifePoint();
	std::stringstream lifePoint;
	lifePoint << std::setw(2) << std::setfill('0') << temp;
	//Điểm của người chơi
	string score = "SCORE - " + Player::GetInstance()->GetScoreString() + " ";
	//Item point
	std::stringstream itemPoint;
	int item = Player::GetInstance()->GetItemPoint();
	itemPoint << std::setw(2) << std::setfill('0') << item;
	
	//Vẽ text
	Text::GetInstance()->DrawString(score + name, 20, 0, 200, 30);
	Text::GetInstance()->DrawString("TIMER - " + timer.str(), 20, 10, 70, 30);
	Text::GetInstance()->DrawString("P - " + lifePoint.str(), 20, 20, 50, 30);
	Text::GetInstance()->DrawString(itemPoint.str(), 74, 20, 20, 30);
	Text::GetInstance()->DrawString("Ninja-", 117, 10, 50, 30);
	Text::GetInstance()->DrawString("Enemy-", 117, 20, 50, 30);
}

void Scence::Render()
{
	RenderText();
	map->drawMap();
	Grid::GetInstance()->RenderObject();
}
