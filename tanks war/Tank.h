#pragma once
#include "Unit.h"

class Tank :public Unit
{
private:
	bool Trackdisplay;//切换履带使用
	ll time_Trackdisplay;//履带切换时间点
	int Tankspeed;//记录坦克类的速度
public:
	Tank(UnitType type, Direction direction, paint_pos pos);
};

