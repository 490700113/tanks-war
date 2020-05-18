#include "Unit.h"



Unit::Unit(UnitType type, Map_pos pos, Direction direction) 
	:type(type),pos_rc(pos),dir(direction)
{

}
Unit::~Unit() 
{
}

/*set函数*/
void Unit::SetPosXY(const Draw_pos& pos)
{
	this->pos_xy = pos;
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
	this->pos_map = pu;
}

/*get函数*/
const Draw_pos& Unit::GetPosXY()const
{
	return pos_xy;
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
	return pos_map;
}

const Map_pos& Unit::GetPosU()const {
	return pos_unit;
}

/*控制类函数*/
bool Unit::move(Direction direction, const Map& map)
{
	Draw_pos pos = GetPosXY();
	Direction dir = GetDirection();

	switch (dir)
	{
	case D_UP:
		SetDirection(D_UP);//修改坦克朝向
		pos.y--;
		break;
	case D_LEFT:
		SetDirection(D_LEFT);//修改坦克朝向
		pos.x--;
		break;
	case D_DOWN:
		SetDirection(D_DOWN);//修改坦克朝向
		pos.y++;
		break;
	case D_RIGHT:
		SetDirection(D_RIGHT);//修改坦克朝向
		pos.x++;
		break;
	default:
		break;
	}
	return true;
}