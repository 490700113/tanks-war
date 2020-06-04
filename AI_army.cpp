#include "AI_army.h"

AI_army::AI_army(UnitType type, Map_pos pos, Direction direction)
	:Tank(type, pos, direction)
{

}

/*控制函数*/
Direction AI_army::ai_move(Direction dir, const Map& map)
{
	if (dir == D_STOP)//如果处于暂停状态
	{ 
		//if (!(rand() % 5))
		//{
		//	dir = (Direction)(rand() % 4);
		//}
	}
	else
	{
		if (!(rand() % 23))
		{
			int ran = rand() % 8;
			if (ran > 3)
			{
				dir = D_STOP;
			}
			else
			{
				dir = (Direction)ran;
			}
		}
	}
	if (dir != D_STOP)//强化ai
	{
		int ran = rand() % 4;
		if (touch(map))
		{
			dir = (Direction)ran;
		}
	}
	return dir;
}

bool AI_army::ai_shoot(Direction dir)
{
	if (!(rand() % 11))
	{
		return true;
	}
	Map_pos pos = GetPosMap();//强化ai
	if (pos.c == 27 || pos.r == 26)
	{
		if (pos.r < 14 && dir == D_RIGHT)
		{
			return true;
		}
		if (pos.r > 15 && dir == D_LEFT)
		{
			return true;
		}
		return true;
	}
	if (pos.r == 14 || pos.r == 15)
	{
		if (pos.c > 22 && dir == D_DOWN)
		{
			return true;
		}
	}
	return false;
}

/*get函数*/
float AI_army::getspeed()const
{
	return Movespeed / 1000.0f;
}