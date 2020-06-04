#pragma once
#include "AllSettings.h"
#include "Tank.h"
#include "Map.h"

const Map_pos army_born_pos = { 2,2 };

class AI_army :public Tank
{
public:
	AI_army(UnitType type = computer, Map_pos pos = army_born_pos, Direction direction = D_DOWN);

	/*控制函数*/
	Direction ai_move(Direction dir, const Map& map);
	bool ai_shoot(Direction dir);

	/*get函数*/
	virtual float getspeed()const;
};

