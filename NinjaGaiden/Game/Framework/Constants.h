﻿#pragma once
// ========= GAME
#define GAME_SCREEN_320_240 0
#define GAME_SCREEN_640_480 1
#define GAME_TITLE L"Ninja Gaiden"
// ========= SOUND PATH
#define SOUND_TRACK_PATH_MAP_1	"sound//STAGE1.mp3"
#define SOUND_TRACK_PATH_MAP_2	"sound//STAGE2.mp3"
#define SOUND_TRACK_PATH_MAP_3	"sound//STAGE3.mid"
#define SOUND_PATH_EFFECT_ATK					"sound///effects/22.wav"
#define SOUND_PATH_EFFECT_ATK_SMALL_SHURIKEN	"sound//effects//10.wav"
#define SOUND_PATH_EFFECT_ATK_BIG_SHURIKEN		"sound//effects//11.wav"
#define SOUND_PATH_EFFECT_ATK_FIRE				"sound//effects//12.wav"
#define SOUND_PATH_EFFECT_JUMP					"sound//effects//02.wav"
#define SOUND_PATH_EFFECT_WOUNDED				"sound//effects//04.wav"
#define SOUND_PATH_EFFECT_DIGEST_FOOD			"sound//effects//06.wav"
#define SOUND_PATH_EFFECT_ENEMY_DIE				"sound//effects//05.wav"
#define SOUND_PATH_EFFECT_ENEMY_GUN				"sound//effects//18.wav"
#define SOUND_PATH_EFFECT_ENEMY_BAZOKA			"sound//effects//19.wav"
#define SOUND_PATH_EFFECT_BOSS_EXPLOSION		"sound//effects//31.wav"
#define SOUND_PATH_EFFECT_BOSS_JUMP				"sound//effects//32.wav"
// ========= SOUND NAME
#define SOUND_TRACK_MAP1			"sound_track_map1"
#define SOUND_TRACK_MAP2			"sound_track_map2"
#define SOUND_TRACK_MAP3			"sound_track_map3"
#define SOUND_ATK					"atk"
#define SOUND_ATK_SMALL_SHURIKEN	"atk_small_shuriken"
#define SOUND_ATK_BIG_SHURIKEN		"atk_big_shuriken"
#define SOUND_ATK_FIRE				"atk_fire"
#define SOUND_JUMP					"jump"
#define SOUND_WOUNDED				"jump"
#define SOUND_DIGEST_FOOD			"digest_food"
#define SOUND_ENEMY_DIE				"enemy_die"
#define SOUND_ENEMY_GUN				"enemy_gun"
#define SOUND_ENEMY_BAZOKA			"enemy_bazoka"
#define SOUND_BOSS_EXPLOSION		"boss_explosion"
#define SOUND_BOSS_JUMP				"boss_jump"
// =========== HUD
#define HEALTH_ID 50
#define HEALTH L"resource\\HUD\\health.PNG"
#define BOX_ID 51
#define BOX L"resource\\HUD\\box.PNG"
#define POINT_ID 52
#define POINT_BOX L"resource\\HUD\\point.PNG"
#define BIG_SHURIKEN_ID 20
#define PATH_BIG_SHURIKEN L"resource\\item.PNG" 
// =========== POINT
#define MANA_POINT_SHURIKEN_SMALL 3
#define MANA_POINT_SHURIKEN_BIG 5
#define MANA_POINT_FIRE 5
// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"resource/player.png"
#define PATH_POS_MAIN_STAND L"resource/main/MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"resource\\main\\MAIN_RUN.txt"
#define PATH_POS_SIT L"resource\\main\\MAIN_SIT.txt"
#define PATH_POS_SIT_ATK L"resource\\main\\MAIN_SIT_ATK.txt"
#define PATH_POS_STAND_ATK L"resource\\main\\MAIN_STAND_ATK.txt"
#define PATH_POS_JUMP L"resource\\main\\MAIN_JUMP.txt"
#define PATH_POS_JUMP_ATK L"resource\\main\\MAIN_JUMP_ATK.txt"
#define PATH_POS_WOUNDED L"resource\\main\\MAIN_WOUNDED.txt"
#define PATH_POS_WEAPON L"resource\\main\\MAIN_USE_WEAPON.txt"
#define PATH_POS_CLIMB L"resource\\main\\MAIN_CLIMB.txt"
// ======== Vũ khí player
#define PATH_POS_SmallShuriken L"resource\\main\\SmallShuriken.txt"
#define PATH_POS_BigShuriken L"resource\\main\\BigShuriken.txt"
#define PATH_POS_CircleFire L"resource\\main\\Circle_Fire.txt"
// =====	Map 1
#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"resource\\Stage1\\Map1.png"
#define PATH_POS_MAP_1 L"resource\\Stage1\\Map1.txt"
#define PATH_POS_GROUND_MAP_1 L"resource\\Stage1\\ground.txt"
#define PATH_POS_ENEMY_MAP_1 L"resource\\Stage1\\enemy.txt"
#define PATH_POS_FOOD_MAP_1 L"resource\\Stage1\\food.txt"
#define PATH_POS_BRICK_MAP_1 L"resource\\Stage1\\brick.txt"
#define PATH_POS_DESTINATION_MAP_1 L"resource\\Stage1\\destination.txt"
// =====	Map 2
#define ID_TEXTURE_MAP_2 200
#define PATH_TEXTURE_MAP_2 L"resource\\Stage2\\Map2.png"
#define PATH_POS_MAP_2 L"resource\\Stage2\\Map2.txt"
#define PATH_POS_GROUND_MAP_2 L"resource\\Stage2\\ground.txt"
#define PATH_POS_FOOD_MAP_2 L"resource\\Stage2\\food.txt"
#define PATH_POS_ENEMY_MAP_2 L"resource\\Stage2\\enemy.txt"
#define PATH_POS_LADDER_MAP_2 L"resource\\Stage2\\ladder.txt"
#define PATH_POS_ROCK_MAP_2 L"resource\\Stage2\\rock.txt"
#define PATH_POS_BRICK_MAP_2 L"resource\\Stage2\\brick.txt"
#define PATH_POS_DESTINATION_MAP_2 L"resource\\Stage2\\destination.txt"
// =====	Map 3
#define ID_TEXTURE_MAP_3 300
#define PATH_TEXTURE_MAP_3 L"resource\\Stage3\\Map3.png"
#define PATH_POS_MAP_3 L"resource\\Stage3\\Map3.txt"
#define PATH_POS_GROUND_MAP_3 L"resource\\Stage3\\ground.txt"
#define PATH_POS_ROCK_MAP_3 L"resource\\Stage3\\rock.txt"
// ========	Enemy
#define ID_TEXTURE_MAP_1_ENEMY 101 
#define ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE 105
#define PATH_TEXTURE_MAP_1_ENEMY_DIE_FIRE L"resource\\Enemy_die.png"
#define PATH_TEXTURE_MAP_1_ENEMY L"resource\\Enemies_Bosses.png"
//=========== Lính vàng cầm kiếm
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_follow L"resource\\enemy\\SoldierSword_follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_atk L"resource\\enemy\\SoldierSword_atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE L"resource\\enemy\\enemy_die.txt"
//=========== Báo vàng
#define PATH_TEXTURE_MAP_1_ENEMY_Panther_follow L"resource\\enemy\\Panther.txt"
//=========== Đại bàng
#define PATH_TEXTURE_MAP_1_ENEMY_Eagle_follow L"resource\\enemy\\Eagle.txt"
//=========== Lính xanh lá chạy 
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierRun L"resource\\enemy\\SoldierRun.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SoldierRun_JUMP L"resource\\enemy\\SoldierRun_JUMP.txt"
//=========== Dơi
#define PATH_TEXTURE_MAP_1_ENEMY_BAT_FOLLOW L"resource\\enemy\\Bat.txt" 
//=========== Boss
#define PATH_TEXTURE_MAP_3_ENEMY_BOSS L"resource\\boss\\BOSS.txt"
#define PATH_TEXTURE_MAP_3_BOOM_BOSS L"resource\\boss\\Boom.txt"
#define PATH_TEXTURE_MAP_3_EXPLOSION_BOSS L"resource\\boss\\Explosion.txt"
//=========== Trạng thái chết của enemy thường
#define PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE L"resource\\enemy\\enemy_die.txt"
//=========== Item Food
#define PATH_TEXTURE_MAP_1_FOOD_UNTOUCH_BUTTERFLY L"resource\\food\\food_untouch_butterfly.txt"
#define PATH_TEXTURE_MAP_1_FOOD_UNTOUCH_BIRD L"resource\\food\\food_untouch_bird.txt"
#define PATH_TEXTURE_MAP_1_FOOD_DEAD	L"resource\\food\\food_dead.txt"
#define PATH_TEXTURE_MAP_1_FOOD_ITEM_POINT_BLUE L"resource\\food\\food_item_point_blue.txt"
#define PATH_TEXTURE_MAP_1_FOOD_ITEM_POINT_RED L"resource\\food\\food_item_point_red.txt"
#define PATH_TEXTURE_MAP_1_FOOD_VASE_BLUE L"resource\\food\\food_vase_blue.txt"
#define PATH_TEXTURE_MAP_1_FOOD_VASE_RED L"resource\\food\\food_vase_red.txt"
#define PATH_TEXTURE_MAP_1_FOOD_TIME L"resource\\food\\food_time.txt"
#define PATH_TEXTURE_MAP_1_FOOD_FIRE L"resource\\food\\food_fire.txt"
#define PATH_TEXTURE_MAP_1_FOOD_SHURIKEN_BLUE L"resource\\food\\food_shuriken_blue.txt"
#define PATH_TEXTURE_MAP_1_FOOD_SHURIKEN_RED L"resource\\food\\food_shuriken_red.txt"
#define PATH_TEXTURE_MAP_1_FOOD_BLOOD L"resource\\food\\food_blood.txt"
//=========== Phù thủy
#define PATH_TEXTURE_MAP_1_ENEMY_WITCH_FOLLOW L"resource\\enemy\\Witch\\follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_WITCH_ATK L"resource\\enemy\\Witch\\atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_WITCH_SWORD L"resource\\enemy\\Witch\\sword.txt"
//=========== Lính cầm súng
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_FOLLOW L"resource\\enemy\\SoliderGun\\follow.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_ATK L"resource\\enemy\\SoliderGun\\atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_BULLET L"resource\\enemy\\SoliderGun\\bullet.txt"
//=========== Lính cầm bazoka
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_DO_NOT_THING L"resource\\enemy\\SoliderBazoka\\do_not_thing.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_ATK L"resource\\enemy\\SoliderBazoka\\atk.txt"
#define PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_BULLET L"resource\\enemy\\SoliderBazoka\\bullet.txt"
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
	BRICK,
	EAGLE,
	BAT,
	DESTINATION
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
	CLIMB,
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

enum FOOD_TYPE {
	ITEM_POINT_BLUE,
	ITEM_POINT_RED,
	VASE_BLUE,
	VASE_RED,
	TIMER,
	FIRE,
	SHURIKEN_BLUE,
	SHURIKEN_RED,
	BLOOD
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
