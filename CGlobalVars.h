#include "SDK.h"

class CGlobalVariables
{
public:
	int iAimbotIndex = -1;
	
	float settings_switch;
	float iMenu_Pos_X = 300;
	float iMenu_Pos_Y = 75;
	float szsubstest;

	float aimbot_switch;
	float aimbot_silent;
	float aimbot_active;
	float aimbot_key;
	float aimbot_hitscan;
	float aimbot_hitbox;
	float aimbot_autoshoot;

	float triggerbot_switch;
	float triggerbot_active;
	float triggerbot_key;
	float triggerbot_headonly;

	float esp_switch;
	float esp_active;
	float esp_enemyonly;
	float esp_box;
	float esp_name;
	float esp_class;
	float esp_health;
	float esp_bones;

	float misc_switch;
	float misc_bunnyhop;
	float misc_autostrafe;
	float misc_noisemaker_spam;
	float misc_anti_aim;
	float misc_anti_aim_x;
	float misc_anti_aim_y;
	float misc_anti_anti_aim;
	float misc_anti_anti_aim_unsafe_x;

	float playerlist_switch;
	float PlayerMode[64] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
};

class COffsets
{
public:
	int iKeyEventOffset = 20, iCreateMoveOffset = 21, iPaintTraverseOffset = 41, iFrameStageOffset = 35;
};