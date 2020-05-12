#pragma once
#include "Unit.h"

class Tank :public Unit
{
public:
	Tank(UnitType type, Direction direction, paint_pos pos);
};

