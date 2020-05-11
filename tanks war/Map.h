#pragma once
#include "AllSettings.h"


//行列坐标
typedef struct
{
	int row, col;
}map_pos;


//地图的类
class Map
{
private:
	char map[map_row_px][map_col_px];//地图数组
public:
	Map();//构造函数

	//关卡选择
	void chooseMap(int level = 1);//选择关卡，level是关卡数
};