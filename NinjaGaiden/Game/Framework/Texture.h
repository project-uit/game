#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include "Game.h"
#include "../Logging/Debug.h"

using namespace std;

#define TRANSPARENT_COLOR D3DCOLOR_XRGB(255, 163, 177)

class Texture
{
	static Texture * _instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	Texture();
	void Add(int id, LPCWSTR filePath, D3DCOLOR trans = D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 Get(int id);

	static Texture * GetInstance() {
		if (_instance == NULL) _instance = new Texture();
		return _instance;
	}
};

