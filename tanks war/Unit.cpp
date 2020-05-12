#include "Unit.h"


Unit::Unit(UnitType type, Direction direction, paint_pos pos) 
	:type(type),dir(direction),pos_xy(pos)
{

}
Unit::~Unit() 
{
}

/*set函数*/
void Unit::SetPosXY(const paint_pos& pos)
{
	this->pos_xy = pos;
}
void Unit::SetDirection(Direction direction)
{
	this->dir = direction;
}

/*get函数*/
const paint_pos& Unit::GetPosXY()const
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

/*控制类函数*/
bool Unit::move(Direction direction, const Map& map)
{

}