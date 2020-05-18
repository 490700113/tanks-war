#pragma once
#include "AllSettings.h"

const Map_pos Home_pos = { 26,14 };

//地图的类
class Map
{
private:
	uc map[map_row_px][map_col_px];//地图数组
	void chooseMap(int level = 1);//选择关卡，level是关卡数
public:
	Map();//构造函数
	
	void ChangeLevel(int level);//切换关卡的函数
	void DestroyMap(const Map_pos& Mpos, const Direction& dir, const Destoryunit& destory);//处理部分被毁的地图
	void DestoryHome();//处理家的情况

	/*get函数*/
	const uc(*GetPos())[map_row_px][map_col_px];//返回地图数组的首地址
	uc GetMPos(const Map_pos& Mpos)const;//返回指定地图行列的数值

	/*set函数*/
	void SetMPos(const Map_pos& Mpos, uc mpos);//修改地图上的数值
};