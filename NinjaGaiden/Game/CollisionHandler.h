#include "Object.h"
class CollisionHandler
{
private:
	Object* obj;
	float collisionTime, nx, ny;
public:
	CollisionHandler(float collisionTime, float nx, float ny, Object* obj = NULL);
	~CollisionHandler();

	static bool Compare(const CollisionHandler* a, const CollisionHandler *b) {
		return a->collisionTime < b->collisionTime;
	}

	float GetCollisionTime() {
		return this->collisionTime;
	}

	float GetNx() {
		return this->nx;
	}

	float GetNy() {
		return this->ny;
	}
};