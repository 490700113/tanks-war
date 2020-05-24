#pragma once
#include "Tank.h"

//const Map_pos P_bron_pos = { 26,10 };
const Map_pos P_bron_pos = { 20,10 };

class Player :public Tank
{
public:
	Player(UnitType type = player, Map_pos pos = P_bron_pos, Direction direction = D_UP);
};

