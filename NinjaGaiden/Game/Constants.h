#pragma once
// ========= GAME
#define GAME_SCREEN_320_240 0
#define GAME_SCREEN_640_480 1
#define GAME_TITLE L"Ninja Gaiden"
// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\player.png"
#define PATH_POS_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"
#define PATH_POS_SIT L"sprite\\main\\MAIN_SIT.txt"
#define PATH_POS_SIT_ATK L"sprite\\main\\MAIN_SIT_ATK.txt"
#define PATH_POS_STAND_ATK L"sprite\\main\\MAIN_STAND_ATK.txt"
#define PATH_POS_JUMP L"sprite\\main\\MAIN_JUMP.txt"
#define PATH_POS_WOUNDED L"sprite\\main\\MAIN_WOUNDED.txt"
// =====	Map 1
#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"sprite\\Stage1\\Map1.png"
#define PATH_POS_MAP_1 L"sprite\\Stage1\\Map1.txt"
#define PATH_POS_GROUND_MAP_1 L"sprite\\Stage1\\ground.txt"
#define PATH_POS_ENEMY_MAP_1 L"sprite\\Stage1\\enemy.txt"
// ========	Enemy
#define ID_TEXTURE_MAP_1_ENEMY 101 
#define PATH_TEXTURE_MAP_1_ENEMY L"sprite\\Enemies_Bosses.png"
//=========== Lính vàng cầm kiếm
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_follow L"sprite\\enemy\\SoldierSword_follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_atk L"sprite\\enemy\\SoldierSword_atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE L"sprite\\enemy\\enemy_die.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DISAPPEAR L"sprite\\enemy\\disappear.txt"
//=========== other
enum OBJECT_TYPE {
	SQUARE,
	MAIN_CHARACTER,
	SOLDIER_SWORD
};

enum PLAYER_STATE {
	STAND,
	RUN,
	STAND_ATK,
	JUMP,
	SIT,
	DIE,
	SIT_ATK,
	WOUNDED
};

enum ENEMY_STATE {
	ATK,
	FOLLOW,
	DEAD,
	DO_NOTHING
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
