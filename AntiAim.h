#pragma once

#include "SDK.h"
#include "Util.h"

class CAntiAim {
public:
	void CreateMove(CBaseEntity* local, CUserCmd* cmd);
};

extern CAntiAim gAntiAim;