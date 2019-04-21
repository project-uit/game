#pragma once
#include <Windows.h>

class GameTime
{
public:
	float elapsedTime;
	float totalGameTime;

	bool Initialize();
	void Update();
private:
	LONGLONG start;
	float frequencySeconds;
};