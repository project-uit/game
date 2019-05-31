#pragma once
#pragma comment(lib, "strmiids.lib") 
#include <dshow.h>
#include <cstdio>

class Mp3
{
private:

public:
	Mp3();
	~Mp3();
	void PlaySoundTrack(const wchar_t* filePath);
};