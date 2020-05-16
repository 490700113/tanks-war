#pragma once
#include "AllSettings.h"


//地图的类
class Map
{
private:
	const char map[map_row_px][map_col_px];//地图数组
	void chooseMap(int level = 1);//选择关卡，level是关卡数
public:
	Map();//构造函数

	void ChangeLevel(int level);//切换关卡的函数

};