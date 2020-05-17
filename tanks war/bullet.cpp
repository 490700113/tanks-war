#include "bullet.h"

Bullet::Bullet(const Unit& tank) :
	Unit(tank.GetMapPos(), bullet, tank.GetDirection()), owner(tank.GetType()) {
	Map_pos unitpos = tank.GetUnitPos();//存修正后的unit坐标（这个函数待补）
	Draw_pos pxpos = GetPosXY();//存修正后的绘图坐标
	//下面修正子弹坐标
	switch (GetDirection()) {
		case UP:
			unitpos.c++;
			//pxpos.x=(float)unitpos.c*
				//下面先不写了 变量太多搞不清楚。。明天弄清楚了再整吧
	}
}