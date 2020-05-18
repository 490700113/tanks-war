#pragma once
#include "AllSettings.h"


//地图的类
class Map
{
private:
	uc map[map_row_px][map_col_px];//地图数组
	void chooseMap(int level = 1);//选择关卡，level是关卡数
public:
	Map();//构造函数
	
	void ChangeLevel(int level);//切换关卡的函数

	/*get函数*/
	const uc(*GetPos())[map_row_px][map_col_px];//返回地图数组的首地址
	uc GetMPos(const Map_pos& Mpos)const;//返回指定地图行列的数值

	/*set函数*/
	void SetMPos(const Map_pos& Mpos, uc mpos);//修改地图上的数值
};