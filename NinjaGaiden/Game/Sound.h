#pragma once
#include "xaudio2.h"
#include "Mmsystem.h"
#include <string>
#include <vector>
using namespace std;
class Sound {
private:
	static Sound* _instance;
	vector<LPCWSTR>* resources;
public:
	Sound();
	~Sound();
	void Play(int index);
	void Stop();
	static Sound* GetInstance();
};

// https://docs.microsoft.com/en-us/previous-versions//dd743680(v=vs.85)