#include "Sound.h"
Sound* Sound::_instance = NULL;
Sound::Sound() {
	resources = new vector<LPCWSTR>();
	resources->push_back(L"123");
}

Sound::~Sound() {
	resources->clear();
	delete resources;
}

void Sound::Play(int index) {
	if (index >= resources->size()) {
		Stop();
		return;
	}
	PlaySound(resources->at(index), NULL, SND_FILENAME);
}

void Sound::Stop() {
	PlaySound(NULL, 0, 0);
}

Sound* Sound::GetInstance() {
	if (_instance == NULL) return new Sound();
	return _instance;
}