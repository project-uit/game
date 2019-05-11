#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "InputDevice.h"
#include "Debug.h"
#include "Texture.h"
#include "Sprite.h"

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
struct Point
{
	Point() { x = y = 0; }
	Point(float px, float py) { x = px;  y = py; }

	Point operator+(const Point &A)
	{
		return Point(x + A.x, y + A.y);
	}

	Point operator-(const Point &A)
	{
		return Point(x - A.x, y - A.y);
	}

	Point operator*(float f) const
	{
		return Point(x * f, y * f);
	}

	float x;
	float y;
};

struct Line
{
	Line(float x1, float y1, float x2, float y2)
	{
		Ax = x1;	Ay = y1;
		Bx = x2;	By = y2;
	}

	float Ax;
	float Ay;
	float Bx;
	float By;
};

class Game
{
private:
	static Game * _instance;

	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;	

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

	LPDIRECTINPUT8       di;       
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	InputDevice * keyHandler;

public:
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, 
		int left, int top, int right, int bottom, int alpha = 255);

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, 
		int left, int top, int right, int bottom, 
		D3DXVECTOR3 position, D3DXVECTOR3 scaling, int alpha = 255);

	// Khởi tạo bàn phím
	void InitKeyboard(InputDevice*);
	int IsKeyDown(int keyCode);
	int IsKeyUp(int keyCode);

	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static Game * GetInstance() {
		if (_instance == NULL) _instance = new Game();
		return _instance;
	};
	HWND GetHWnd() { return this->hWnd; }
	static bool AABB(RECT r1, RECT r2);
	static bool AABB_LineLine(Line A, Line B);
	static bool AABB_BoxLine(RECT rect, Line L);
	static void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float &t, float &nx, float &ny);
	~Game();
};

