#include "Item.h"
Item::Item()
{
	
}

Item::~Item()
{

}

void Item::Update(float t)
{
	Object::Update(t);
	RECT rect = sprite->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	Object::PlusPosition(this->deltaX, this->deltaY);
	sprite->NextSprite();
}

void Item::Render()
{
	sprite->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
}
void Item::HandleCollision(vector<Object*> *object) {

}

