#include "SDK.h"
#include "Client.h"
#include "Util.h"
#include "Aimbot.h"
#include "Triggerbot.h"
#include "Misc.h"
#include "AntiAntiAim.h"
#include "AntiAim.h"

//============================================================================================
bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, CUserCmd* pCommand)
{
	VMTManager& hook = VMTManager::GetHook(ClientMode); //Get a pointer to the instance of your VMTManager with the function GetHook.
	bool bReturn = hook.GetMethod<bool(__thiscall*)(PVOID, float, CUserCmd*)>(gOffsets.iCreateMoveOffset)(ClientMode, input_sample_frametime, pCommand); //Call the original.
	try
	{
		if (!pCommand->command_number)
			return false;

		CBaseEntity* pLocal = GetBaseEntity(me); 

		if (!pLocal)
			return bReturn;

		gMisc.Run(pLocal, pCommand);
		gAim.Run(pLocal, pCommand);
		gTrigger.Run(pLocal, pCommand);
		gAntiAim.CreateMove(pLocal, pCommand);
	}
	catch(...)
	{
		Log::Fatal("Failed Hooked_CreateMove");
	}
	return false/*bReturn*/;
}
//============================================================================================
int __fastcall Hooked_KeyEvent(PVOID CHLClient, int edx, int eventcode, int keynum, const char *currentBinding)
{
	if (eventcode == 1)
	{
		if (keynum == 72) //insert
		{
			gCheatMenu.bMenuActive = !gCheatMenu.bMenuActive;
		}

		if (gCheatMenu.bMenuActive)
		{
			if (keynum == 88 || keynum == 112) // Up
			{

				if (gCheatMenu.iMenuIndex > 0) gCheatMenu.iMenuIndex--;
				else gCheatMenu.iMenuIndex = gCheatMenu.iMenuItems - 1;
				return 0;

			}
			else if (keynum == 90 || keynum == 113) // Down
			{
				if (gCheatMenu.iMenuIndex < gCheatMenu.iMenuItems - 1) gCheatMenu.iMenuIndex++;
				else gCheatMenu.iMenuIndex = 0;
				return 0;

			}
			else if (keynum == 89 || keynum == 107) // Left
			{
				if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
				{
					gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] -= gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] < gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin)
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax;
				}
				return 0;

			}
			else if (keynum == 91 || keynum == 108) // Right
			{
				if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
				{
					gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] += gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] > gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax)
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin;
				}
				return 0;

			}

		}
	}

	VMTManager &hook = VMTManager::GetHook(CHLClient); // Get a pointer to the instance of your VMTManager with the function GetHook.
	return hook.GetMethod<int(__thiscall *)(PVOID, int, int, const char *)>(gOffsets.iKeyEventOffset)(CHLClient, eventcode, keynum, currentBinding); // Call the original.
}
//============================================================================================
void __fastcall Hooked_FrameStage(PVOID CHLClient, int edx, ClientFrameStage_t stage) {
	VMTManager& hook = VMTManager::GetHook(CHLClient);

	bool frame_modify = true;

	switch (stage) {
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		gAntiAntiAim.PostDataUpdateStart(); // this is acting as a simple anti anti aim, do not expect too much out of this.
		break;
	default:
		frame_modify = false;
		break;
	}

	hook.GetMethod<void(__thiscall*)(PVOID, ClientFrameStage_t)>(gOffsets.iFrameStageOffset)(CHLClient, stage); // call the original but don't return, since this is a void.
}
//============================================================================================