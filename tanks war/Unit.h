#pragma once
#include "AllSettings.h"
#include "Map.h"
#include<vector>

class Unit
{
private:
	Draw_pos pos_xy;//绘画坐标
	Map_pos pos_rc;//地图坐标
	UnitType type;//单元的类型
	Direction dir;//方向
	Map_pos posu; //单位移动时的坐标
	Draw_pos pos_xy_end; //绘图结束时的坐标
	
public:
	Unit(UnitType type, Map_pos pos, Direction direction);//构造函数
	Unit();
	virtual ~Unit();//虚析构函数
	friend class CWindows;
	/*set函数*/
	void SetPosXY(const Draw_pos& pos);//绘图像素点
	void SetEndPXY(const Draw_pos& pos);//设置绘图终点
	void SetDirection(Direction direction);//改变方向
	void SetPosMap(const Map_pos& pu);//设置单位对齐地图的坐标
	void SetPosU(const Map_pos& pu);//设置更加精细的坐标（修正）

	/*get函数*/
	const Draw_pos& GetPosXY()const;//获取当前绘画坐标
	const Draw_pos& GetEndPosXY()const;//获取终点绘画坐标
	const UnitType& GetType()const;//获取单元类型
	const Direction& GetDirection()const;//获取方向
	const Map_pos& GetPosMap()const;//获取地图坐标
	const Map_pos& GetPosU()const;//获取更加精细的地图坐标
	virtual float getspeed()const;//获取速度


	/*控制类函数*/
	virtual bool move(Direction direction, const Map& map) = 0;//移动函数
	virtual bool to_next();//判断能否进行下一步移动
	virtual bool touch(const Map& map)const;//判断是否有碰撞
};