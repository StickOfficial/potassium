#include "AntiAim.h"

CAntiAim gAntiAim;

void CAntiAim::CreateMove(CBaseEntity* local, CUserCmd* cmd) {
	old_movement_t old_mov = old_movement_t();

	if (!local ||
		!cmd) {
		return;
	}

	if (!gCvars.misc_anti_aim) {
		return;
	}

	old_mov.angle = cmd->viewangles;
	old_mov.fwd = cmd->forwardmove;
	old_mov.sdm = cmd->sidemove;

	if (gCvars.misc_anti_aim > 0) {
		if (gCvars.misc_anti_aim_x == 1) {
			// static up:
			cmd->viewangles.x = -89.0f;
		}
		else if (gCvars.misc_anti_aim_x == 2) {
			// static down:
			cmd->viewangles.x = +89.0f;
		}
		else if (gCvars.misc_anti_aim_x == 3) {
			// fake up:
			cmd->viewangles.x = -271.0f;
		}
		else if (gCvars.misc_anti_aim_x == 4) {
			// fake down:
			cmd->viewangles.x = +271.0f;
		}
	}

	if (gCvars.misc_anti_aim_y > 0) {
		if (gCvars.misc_anti_aim_y == 1) {
			// static left:
			cmd->viewangles.y -= 90.0f;
		}
		else if (gCvars.misc_anti_aim_y == 2) {
			// static right:
			cmd->viewangles.y += 90.0f;
		}
		else if (gCvars.misc_anti_aim_y == 3) {
			// dynamic spin:
			cmd->viewangles.y = cmd->tick_count * 11 % 365;
		}
		else if (gCvars.misc_anti_aim_y == 4) {
			// fake sideways:
			cmd->viewangles.y = cmd->tick_count * 180 % 365;
		}
	}

	Util->FixMovementForUserCmd(cmd, old_mov);
}