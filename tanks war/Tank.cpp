#include "Tank.h"



Tank::Tank(UnitType type, Direction direction, Map_pos pos)
	:Unit(type, direction, pos)
{
	Trackdisplay = false;
	time_Trackdisplay = 0;
}

/*get函数*/
bool Tank::GetTrackState() const//获取履带状态
{
	return Trackdisplay;
}
//int Tank::GetTankspeed() const//获取坦克速度
//{
//	return Tankspeed;
//}

/*控制函数*/
bool Tank::move(Direction direction, const Map& map)//坦克移动
{

	return Unit::move(direction, map);
}