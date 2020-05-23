#include "Tank.h"
#include"time.h"

Tank::Tank(UnitType type, Map_pos pos, Direction direction)
	:Unit(type, pos, direction)
{
	Trackdisplay = false;
	time_Trackdisplay = 0;
}

/*get函数*/
bool Tank::GetTrackState() const//获取履带状态
{
	return Trackdisplay;
}

/*控制函数*/
bool Tank::move(Direction direction, const Map& map)//坦克移动
{
	retrackstate();
	return Unit::move(direction, map);
}

void Tank::retrackstate() {
	ull renewclock = (ull)(multiple_px) / (Movespeed / 16);
	ull cur = time::Gettime();
	if (cur - time_Trackdisplay >= renewclock) {
		time_Trackdisplay = cur;
		Trackdisplay = !Trackdisplay;
	}
}