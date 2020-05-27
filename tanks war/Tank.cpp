#include "Tank.h"
#include"time.h"
#define ul unsigned long 
Tank::Tank(UnitType type, Map_pos pos, Direction direction)
	:Unit(type, pos, direction)
{
	Trackdisplay = false;
	time_Trackdisplay = 0;
	life = max_life;
}

Tank::Tank() {
}

//void Tank::generateenemy() {
//	Map_pos a;
//	a.r = 2, a.c = 2;
//	Tank* newtank = new Tank(computer, a, D_DOWN);
//	return *newtank;
//}

void Tank::generateplayer() {
	Map_pos a;
	a.r = 26, a.c = 10;
	SetPosMap(a);

}

void deletetank(Tank &t) {
	t.life = 0;
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
	DWORD renewclock = (DWORD)(multiple_px) / (Movespeed / 16);
	DWORD cur = time::Gettime();
	if (cur - time_Trackdisplay >= renewclock) {
		time_Trackdisplay = cur;
		Trackdisplay = !Trackdisplay;
	}
}