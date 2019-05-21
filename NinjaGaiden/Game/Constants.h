#pragma once
// ========= GAME
#define GAME_SCREEN_320_240 0
#define GAME_SCREEN_640_480 1
#define GAME_TITLE L"Ninja Gaiden"
// =========== HUD
#define HEALTH_ID 50
#define HEALTH L"sprite\\HUD\\health.PNG"
#define BOX_ID 51
#define BOX L"sprite\\HUD\\box.PNG"
#define POINT_ID 52
#define POINT_BOX L"sprite\\HUD\\point.PNG"
// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\player.png"
#define PATH_POS_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"
#define PATH_POS_SIT L"sprite\\main\\MAIN_SIT.txt"
#define PATH_POS_SIT_ATK L"sprite\\main\\MAIN_SIT_ATK.txt"
#define PATH_POS_STAND_ATK L"sprite\\main\\MAIN_STAND_ATK.txt"
#define PATH_POS_JUMP L"sprite\\main\\MAIN_JUMP.txt"
#define PATH_POS_JUMP_ATK L"sprite\\main\\MAIN_JUMP_ATK.txt"
#define PATH_POS_WOUNDED L"sprite\\main\\MAIN_WOUNDED.txt"
#define PATH_POS_WEAPON L"sprite\\main\\MAIN_USE_WEAPON.txt"
// ======== Vũ khí player
#define PATH_POS_SmallShuriken L"sprite\\main\\SmallShuriken.txt"
#define PATH_POS_BigShuriken L"sprite\\main\\BigShuriken.txt"
#define PATH_POS_CircleFire L"sprite\\main\\Circle_Fire.txt"
// =====	Map 1
#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"sprite\\Stage1\\Map1.png"
#define PATH_POS_MAP_1 L"sprite\\Stage1\\Map1.txt"
#define PATH_POS_GROUND_MAP_1 L"sprite\\Stage1\\ground.txt"
#define PATH_POS_ENEMY_MAP_1 L"sprite\\Stage1\\enemy.txt"
#define PATH_POS_FOOD_MAP_1 L"sprite\\Stage1\\food.txt"
// =====	Map 2
#define ID_TEXTURE_MAP_2 200
#define PATH_TEXTURE_MAP_2 L"sprite\\Stage2\\Map2.png"
#define PATH_POS_MAP_2 L"sprite\\Stage2\\Map2.txt"
#define PATH_POS_GROUND_MAP_2 L"sprite\\Stage2\\ground.txt"
#define PATH_POS_ENEMY_MAP_2 L"sprite\\Stage2\\enemy.txt"
// =====	Map 3
#define ID_TEXTURE_MAP_3 300
#define PATH_TEXTURE_MAP_3 L"sprite\\Stage3\\Map3.png"
#define PATH_POS_MAP_3 L"sprite\\Stage3\\Map3.txt"
#define PATH_POS_GROUND_MAP_3 L"sprite\\Stage3\\ground.txt"
// ========	Enemy
#define ID_TEXTURE_MAP_1_ENEMY 101 
#define ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE 105
#define PATH_TEXTURE_MAP_1_ENEMY_DIE_FIRE L"sprite\\Enemy_die.png"
#define PATH_TEXTURE_MAP_1_ENEMY L"sprite\\Enemies_Bosses.png"
//=========== Lính vàng cầm kiếm
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_follow L"sprite\\enemy\\SoldierSword_follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_atk L"sprite\\enemy\\SoldierSword_atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE L"sprite\\enemy\\enemy_die.txt"
//=========== Báo vàng
#define PATH_TEXTURE_MAP_1_ENEMY_Panther_follow L"sprite\\enemy\\Panther.txt"
//=========== Đại bàng
#define PATH_TEXTURE_MAP_1_ENEMY_Eagle_follow L"sprite\\enemy\\Eagle.txt"
//=========== Boss
#define PATH_TEXTURE_MAP_3_ENEMY_BOSS L"sprite\\boss\\BOSS.txt"
#define PATH_TEXTURE_MAP_3_BOOM_BOSS L"sprite\\boss\\Boom.txt"
//=========== Trạng thái chết của enemy thường
#define PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE L"sprite\\enemy\\enemy_die.txt"
//=========== Item food 1
#define PATH_TEXTURE_MAP_1_FOOD_UNTOUCH L"sprite\\food\\food_untouch.txt"
#define PATH_TEXTURE_MAP_1_FOOD_DEAD	L"sprite\\food\\food_dead.txt"
#define PATH_TEXTURE_MAP_1_FOOD_BLOOD_BLUE L"sprite\\food\\food_blood_blue.txt"
#define PATH_TEXTURE_MAP_1_FOOD_BLOOD_RED L"sprite\\food\\food_blood_red.txt"
#define PATH_TEXTURE_MAP_1_FOOD_DARTS_BLUE L"sprite\\food\\food_darts_blue.txt"
#define PATH_TEXTURE_MAP_1_FOOD_DARTS_RED L"sprite\\food\\food_darts_red.txt"
#define PATH_TEXTURE_MAP_1_FOOD_ITEM_BLUE L"sprite\\food\\food_item_blue.txt"
#define PATH_TEXTURE_MAP_1_FOOD_ITEM_RED L"sprite\\food\\food_item_red.txt"
#define PATH_TEXTURE_MAP_1_FOOD_FIRE L"sprite\\food\\food_fire.txt"
#define PATH_TEXTURE_MAP_1_FOOD_TIME L"sprite\\food\\food_time.txt"
//=========== Phù thủy
#define PATH_TEXTURE_MAP_1_ENEMY_WITCH_FOLLOW L"sprite\\enemy\\Witch\\follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_WITCH_ATK L"sprite\\enemy\\Witch\\atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_WITCH_SWORD L"sprite\\enemy\\Witch\\sword.txt"
//=========== Lính cầm súng
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_FOLLOW L"sprite\\enemy\\SoliderGun\\follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_ATK L"sprite\\enemy\\SoliderGun\\atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_BULLET L"sprite\\enemy\\SoliderGun\\bullet.txt"
//=========== Lính cầm bazoka
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_DO_NOT_THING L"sprite\\enemy\\SoliderBazoka\\do_not_thing.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_ATK L"sprite\\enemy\\SoliderBazoka\\atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_BULLET L"sprite\\enemy\\SoliderBazoka\\bullet.txt"
//=========== other
enum OBJECT_TYPE {
	SQUARE,
	MAIN_CHARACTER,
	SOLDIER_SWORD,
	PANTHER,
	SMALL_SHURIKEN,
	BIG_SHURIKEN,
	CIRCLE_FIRE,
	BOSS, 
	BOOM_BOSS,
	WITCH,
	WITCH_SWORD,
	SOLIDER_GUN,
	BULLET,
	SOLIDER_BAZOKA,
	SOLIDER_RUN,
	FOOD,
	LADDER,
	ROCK,
	EAGLE
};

enum BULLET_TYPE {
	GUN,
	BAZOKA
};

enum PLAYER_STATE {
	STAND,
	RUN,
	STAND_ATK,
	JUMP,
	JUMP_ATK,
	SIT,
	DIE,
	SIT_ATK,
	WOUNDED,
	USE_WEAPON
};

enum ENEMY_STATE {
	ATK,
	FOLLOW,
	DEAD,
	DO_NOTHING,
	THROW,
	HIGH_JUMP,
	FLY,
	INVISIBLE
};

enum FOOD_STATE {
	UNTOUCH,
	TOUCHED,
	DIGESTED,
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
