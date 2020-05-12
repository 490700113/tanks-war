#pragma once
#include "AllSettings.h"
#include "Map.h"



class Unit
{
private:
	paint_pos pos_xy;//绘画坐标
//	map_pos pos_rc;//地图坐标    --后面再整这玩意儿
	UnitType type;//单元的类型
	Direction dir;//方向
public:
	Unit(UnitType type, Direction direction, paint_pos pos);//构造函数
	virtual ~Unit();//虚析构函数

	/*set函数*/
	void SetPosXY(const paint_pos& pos);//绘图像素点
	void SetDirection(Direction direction);//改变方向

	/*get函数*/
	const paint_pos& GetPosXY()const;//获取当前绘画坐标
	const UnitType& GetType()const;//获取单元类型
	const Direction& GetDirection()const;//获取方向

	/*控制类函数*/
	virtual bool move(Direction direction, const Map& map);//移动函数

};