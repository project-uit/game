#pragma once
// ========= GAME
#define GAME_SCREEN_320_240 0
#define GAME_SCREEN_640_480 1
#define GAME_TITLE L"Ninja Gaiden"
// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\sprite_ninja.png"
#define PATH_POS_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"
#define PATH_POS_SIT L"sprite\\main\\MAIN_SIT.txt"
#define PATH_POS_SIT_ATK L"sprite\\main\\MAIN_SIT_ATK.txt"
#define PATH_POS_STAND_ATK L"sprite\\main\\MAIN_STAND_ATK.txt"
#define PATH_POS_JUMP L"sprite\\main\\MAIN_JUMP.txt"

#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"sprite\\Stage1\\texture.png"
#define PATH_POS_MAP_1 L"sprite\\Stage1\\map.txt"
#define PATH_POS_GROUND_MAP_1 "sprite\\Stage1\\ground.txt"

// ========= OBJECT =========
enum OBJECT_TYPE {
	BRICK,
	MAIN_CHARACTER
};

// ========== MAIN CHARACTER STATE ==========
enum PLAYER_STATE {
	STAND,
	RUN,
	STAND_ATK,
	JUMP,
	SIT,
	DIE,
	SIT_ATK
};

enum DIRECTION {
	LEFT,
	RIGHT
};

enum SCENCE {
	SCENCE_1,
	SCENCE_2,
	SCENCE_3
};
