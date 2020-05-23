#include "Unit.h"

Unit::Unit(UnitType type, Map_pos pos, Direction direction) 
	:type(type),pos_rc(pos),dir(direction)
{
	posu.r = pos.r * 2;
	posu.c = pos.c * 2;
	pos_xy.x = (float)pos.c * map_px;
	pos_xy.y = (float)pos.r * map_px;
	pos_xy_end = pos_xy;
}

Unit::~Unit() 
{
}

/*set函数*/
void Unit::SetPosXY(const Draw_pos& pos)
{
	this->pos_xy = pos;
}
void Unit::SetEndPXY(const Draw_pos& pos) {
	this->pos_xy_end = pos;
}

void Unit::SetDirection(Direction direction)
{
	this->dir = direction;
}
void Unit::SetPosU(const Map_pos& pu) {
	this->posu = pu;
	pos_xy_end.x = (float)pu.c * half_map_px;
	pos_xy_end.y = (float)pu.r * half_map_px;
}

void Unit::SetPosMap(const Map_pos& pu) {
	this->pos_rc = pu;
}

/*get函数*/
const Draw_pos& Unit::GetPosXY()const
{
	return pos_xy;
}

const Draw_pos& Unit::GetEndPosXY()const {
	return pos_xy_end;
}

const UnitType& Unit::GetType()const
{
	return type;
}
const Direction& Unit::GetDirection()const
{
	return dir;
}

const Map_pos& Unit::GetPosMap()const {
	return pos_rc;
}

const Map_pos& Unit::GetPosU()const {
	return posu;
}

//float Unit::GetSpeed()const {
//	return 0;//由继承类完成，默认设为0 
//}

/*控制类函数*/
bool Unit::move(Direction direction, const Map& map)
{
	//Draw_pos pos = GetPosXY();
	Direction dir = GetDirection();
	Map_pos pos_map = GetPosMap();
	Map_pos u_map = GetPosU();

	if ((direction - dir) % 2 != 0) {//转90度时，对齐地图坐标
		switch (dir) {
			case D_UP:
				if (u_map.r % 2) u_map.r -= 1;
				break;

			case D_LEFT:
				if (u_map.c % 2) u_map.c -= 1;
				break;
			
			case D_DOWN:
				if (u_map.r % 2) u_map.r += 1;
				break;

			case D_RIGHT:
				if (u_map.c % 2) u_map.c += 1;
				break;
			default:
				break;
		}
		pos_map.r = u_map.r / 2;
		pos_map.c = u_map.c / 2;
		SetPosU(u_map);
		SetPosMap(pos_map);
		SetPosXY(GetEndPosXY());
	}

	switch (direction) {//根据移动方向再修正一次位置
		case D_UP:
			pos_map.r = u_map.r / 2 + u_map.r % 2;
			break;
		case D_LEFT:
			pos_map.c = u_map.c / 2 + u_map.c % 2;
			break;
		case D_DOWN:
			pos_map.r = u_map.r / 2;
			break;
		case D_RIGHT:
			pos_map.c = u_map.c / 2;
			break;
		default:
			break;
	}
	SetPosMap(pos_map);

	switch (direction)
	{
	case D_UP:
		SetDirection(D_UP);//修改坦克朝向
		if(!touch(map)) u_map.r--;
		break;
	case D_LEFT:
		SetDirection(D_LEFT);//修改坦克朝向
		if (!touch(map)) u_map.c--;
		break;
	case D_DOWN:
		SetDirection(D_DOWN);//修改坦克朝向
		if (!touch(map)) u_map.r++;
		break;
	case D_RIGHT:
		SetDirection(D_RIGHT);//修改坦克朝向
		if (!touch(map)) u_map.c++;
		break;
	default:
		break;
	}
	if(u_map==GetPosU()) return true;//有碰撞
	SetPosU(u_map);
	dir = GetDirection();
	switch (dir) {//再根据方向刷新地图坐标位置
		case D_UP:
			pos_map.r = u_map.r / 2 + u_map.r % 2;
			break;
		case D_LEFT:
			pos_map.c = u_map.c / 2 + u_map.c % 2;
			break;
		case D_DOWN:
			pos_map.r = u_map.r / 2;
			break;
		case D_RIGHT:
			pos_map.c = u_map.c / 2;
			break;
		default:
			break;
	}
	SetPosMap(pos_map);
	return false;
}

bool Unit::to_next()
{
	Draw_pos st = GetPosXY();
	Draw_pos ed = GetEndPosXY();
	float v = Movespeed / 1000.0f;
	Direction dir = GetDirection();
	switch (dir) {//判断是否刷新当前坐标
		case D_UP:
			if (st.y > ed.y) st.y = st.y - v;
			break;
		case D_LEFT:
			if (st.x > ed.x)	st.x = st.x - v;
			break;
		case D_DOWN:
			if (st.y < ed.y) st.y = st.y + v;
			break;
		case D_RIGHT:
			if (st.x < ed.x)	st.x = st.x + v;
			break;
		default:
			break;
	}
	SetPosXY(st);
	switch (dir) {//判断是否刷新当前坐标
		case D_UP:
			if (st.y <= ed.y) return true;
			break;
		case D_LEFT:
			if (st.x <= ed.x)	return true;
			break;
		case D_DOWN:
			if (st.y >= ed.y) return true;
			break;
		case D_RIGHT:
			if (st.x >= ed.x)	return true;
			break;
		default:
			break;
	}
	return false;
}
bool Unit::touch(const Map& map)const
{
	Map_pos pos = GetPosMap();
	Map_pos check[2] = { pos,pos };
	Direction dir = GetDirection();
	switch (dir) {
		case D_UP:
			check[0].r--;
			check[1].r--;
			check[1].c++;
			break;
		case D_LEFT:
			check[0].c--;
			check[1].c--;
			check[1].r++;
			break;
		case D_DOWN:
			check[0].r = check[0].r + 2;
			check[1].r = check[1].r + 2;
			check[1].c++;
		case D_RIGHT:
			check[0].c = check[0].c + 2;
			check[1].c = check[1].c + 2;
			check[1].r++;
			break;
		default:
			break;
	}

	for (int i = 0; i < 2; i++) {
		uc cmp = map.GetMPos(check[i]);
		if (cmp > Empty && cmp <= Water || cmp >= Home_Live_LU && cmp <= Home_Die_RD) return true;
	}
	return false;
}