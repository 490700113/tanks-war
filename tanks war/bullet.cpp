#include "bullet.h"

Bullet::Bullet(const Unit& tank) :
	Unit(bullet, tank.GetPosMap(), tank.GetDirection()), owner(tank.GetType()) {
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

bool Bullet::move(Direction dir, const Map& map) {
	Map_pos posu = GetPosU();
	Map_pos posm = GetPosMap();
	switch (dir) {//修正posm
		case D_UP:
			posm.r = posu.r / 2;
			break;
		case D_LEFT:
			posm.c = posu.c / 2;
			break;
		case D_DOWN:
			posm.r = posu.r / 2 - posu.r % 2;
			break;
		case D_RIGHT:
			posm.c = posu.c / 2 - posu.c % 2;
			break;
		default:
			break;
	}
	SetPosMap(posm);
	switch (dir) {//开始移动
		case D_UP:
			if (!touch(map)) posu.r--;
			break;
		case D_LEFT:
			if (!touch(map)) posu.c--;
			break;
		case D_DOWN:
			if (!touch(map)) posu.r++;
			break;
		case D_RIGHT:
			if (!touch(map)) posu.c++;
			break;
		default:
			break;
	}
	if (posu == GetPosU()) return true; //运动后和原来位置相同，说明发生碰撞
	SetPosU(posu);
	return false;
}

float Bullet::getspeed()const {
	if (owner == computer) return 3.840;
	else return 4.840;
}

bool Bullet::touch(const Map& map) {
	Direction dir = GetDirection();
	recheckpoint(map);//计算需要进行体积碰撞判定的点
	for (int i = 0; i < lcount; i++) {
		for (int j = 0; j < mcount; i++) {
			if (checkval[j] > 0 && checkval[j] < Border) {
				if (flag[i][j])  return true;
			}
			if (checkval[j] >= Home_Live_LU && checkval[j] <= Home_Live_RD) return true;
		}
	}
	return false;
}

unsigned int Bullet::getowner()const {
	return owner;
}

const Map_pos(*Bullet::GetCPos() const)[mcount] {
	return &checkpos;
}

const char(*Bullet::GetCVal() const)[mcount] {
	return &checkval;
}

const bool(*Bullet::GetTouch() const)[lcount][mcount]{
	return &flag;
}

const Draw_pos Bullet::GetBoomPos()const {
	Draw_pos pos = GetEndPosXY();
	pos.x -= 40;
	pos.y -= 40;
	int offset[2] = { 0,0 };//坐标偏移，防止爆炸点重合
	bool flag[2] = { 0,0 };//控制偏移是加法还是减法
	for (int i = 0; i < 2; i++) {
		flag[i] = rand() % 2;
		offset[i] = rand() % 4 * 2;
	}
	pos.x += (float)pow(-1, flag[0]) * offset[0];
	pos.y += (float)pow(-1, flag[1]) * offset[1];
	return pos;
}

void Bullet::recheckpoint(const Map& map) {
	recheckpos();
	recheckval(map);
	recheckflag();
}

void Bullet::recheckpos() {
	for (int i = 0; i < mcount; i++) checkpos[i] = GetPosMap();//获取当前坐标，有两个碰撞判定点
	Direction dir = GetDirection();
	//计算需要进行体积碰撞的两个点
	switch (dir) {
		case D_UP:
		case D_DOWN:
			checkpos[1].c++;
			break;
		case D_LEFT:
		case D_RIGHT:
			checkpos[1].r++;
			break;
		default:
			break;
	}
}

void Bullet::recheckval(const Map& map) {
	for (int i = 0; i < mcount; i++) checkval[i] = map.GetMPos(checkpos[i]);
}

void Bullet::recheckflag() {
	//初始化
	for (int i = 0; i < lcount; i++)
		for (int j = 0; j < mcount; j++) flag[i][j] = 0;
	Direction dir = GetDirection();
	switch (dir) {
		case D_UP:
			//第一层砖
			if (checkval[0] & dr) {
				flag[0][0] = true;
			}
			if (checkval[1] & dl) {
				flag[0][1] = true;
			}
			//第二层砖
			if (checkval[0] && ur) {
				flag[1][0] = true;
			}
			if (checkval[1] & ul) {
				flag[1][1] = true;
			}
			break;
		case D_LEFT:
			if (checkval[0] & dr) {
				flag[0][0] = true;
			}
			if (checkval[1] & ur) {
				flag[0][1] = true;
			}
			//第二层砖
			if (checkval[0] && dl) {
				flag[1][0] = true;
			}
			if (checkval[1] & ul) {
				flag[1][1] = true;
			}
			break;
		case D_DOWN:
			if (checkval[0] & ur) {
				flag[0][0] = true;
			}
			if (checkval[1] & ul) {
				flag[0][1] = true;
			}
			//第二层砖
			if (checkval[0] && dr) {
				flag[1][0] = true;
			}
			if (checkval[1] & dl) {
				flag[1][1] = true;
			}
			break;
		case D_RIGHT:
			if (checkval[0] & dl) {
				flag[0][0] = true;
			}
			if (checkval[1] & ul) {
				flag[0][1] = true;
			}
			//第二层砖
			if (checkval[0] && dr) {
				flag[1][0] = true;
			}
			if (checkval[1] & ur) {
				flag[1][1] = true;
			}
			break;
		default:
			break;
	}
}