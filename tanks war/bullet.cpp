#include "bullet.h"

Bullet::Bullet(const Unit& tank) :
	Unit(bullet, tank.GetDirection(), tank.GetPosMap()), owner(tank.GetType()) {
	Map_pos unitpos = tank.GetPosU();//存修正后的unit坐标（这个函数待补）
	Draw_pos pxpos = GetPosXY();//存修正后的绘图坐标
	//下面修正子弹坐标
	switch (GetDirection()) {
		case D_UP:
			unitpos.c++;
			pxpos.x = (float)unitpos.c * half_map_px + half_map_px / 2;
			break;
		case D_LEFT:
			unitpos.r++;
			pxpos.y = (float)unitpos.r * half_map_px + half_map_px / 2;
			break;
		case D_DOWN:
			unitpos.c++;
			unitpos.r = unitpos.r + 3;
			pxpos.y = (float)unitpos.r * half_map_px + half_map_px / 2;
			pxpos.x = (float)unitpos.c * half_map_px + half_map_px / 2;
			break;
		case D_RIGHT:
			unitpos.r++;
			unitpos.c = unitpos.c + 3;
			pxpos.y = (float)unitpos.r * half_map_px + half_map_px / 2;
			pxpos.x = (float)unitpos.c * half_map_px + half_map_px / 2;
			break;
		default:
			break;
	}
	SetPosU(unitpos);
	SetPosXY(pxpos);
	unitpos.r = unitpos.r / 2;
	unitpos.c = unitpos.c / 2;
	SetPosMap(unitpos);
	for (int i = 0; i < lcount; i++)
		for (int j = 0; j < mcount; j++) flag[i][j] = false;
	for (int i = 0; i < mcount; i++) {
		checkpos[i] = GetPosMap();
		checkval[i] = 0;
	}
}