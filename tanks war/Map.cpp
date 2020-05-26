#include <iostream>
#include <fstream>
#include "Map.h"
#include "Picture.h"
using namespace std;

Map::Map()
{
	//map2[2][2] = 1;
	//map[26][14] = 1;
	chooseMap();
}

void Map::chooseMap(int level)
{
	ifstream file_map;//地图文件流
	wstring temp;//保存地图文件名

	//以下来自网络

	TCHAR temp_map[_MAX_PATH];
	::GetTempPath(_MAX_PATH, temp_map);
	_tcscat_s(temp_map, _T("map.txt"));
	//map提取为临时文件
	ExtractResource(temp_map, _T("MAP"), _T("map"));

	//获取地图文件
	temp = temp_map;
	file_map.open(temp);
	if (!file_map.is_open())//判断是否打开成功
	{
		printf("地图文件打开失败！\n");
		exit(1);
	}

	level--;
	file_map.seekg(level * map_row_px * map_col_px * 3 + level);//将文件制定到制定字节

	int temp_num;//暂存文件读取的整数，
	for (size_t r = 0; r < map_row_px; r++)
	{
		for (size_t c = 0; c < map_col_px; c++)
		{
			file_map >> hex >> temp_num;
			map[r][c] = temp_num;
		}
	}
	file_map.close();

	// 删除临时文件
	DeleteFile(temp_map);
}

void Map::ChangeLevel(int level)
{
	chooseMap(level);
}

void Map::DestroyMap(const Map_pos& Mpos, const Direction& dir, const Destoryunit& destory)
{
	if (destory == wonderful) return;
	if (destory == omg)
	{
		SetMPos(Mpos, Empty);
		return;
	}
	uc temp = map[Mpos.r][Mpos.c];//保存地图坐标
	bool flag[4] = { 0 };//分别判断四个方向还在不在
	if (temp & 1)
	{
		flag[D_UP] = 1;
		flag[D_LEFT] = 1;
	}
	temp >>= 1;
	if (temp & 1)
	{
		flag[D_UP] = true;
		flag[D_RIGHT] = true;
	}
	temp >>= 1;
	if (temp & 1)
	{
		flag[D_DOWN] = true;
		flag[D_LEFT] = true;
	}
	temp >>= 1;
	if (temp & 1)
	{
		flag[D_DOWN] = true;
		flag[D_RIGHT] = true;
	}
	//开始销毁砖块了
	switch (dir)
	{
	case D_UP:
		if (flag[D_DOWN])
		{
			//如果下半部分存在那么就消除下半部分
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_up;
		}
		else
		{
			//下半部分不在证明全部玩完了
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_no;
		}
		break;
	case D_LEFT:
		if (flag[D_RIGHT])
		{
			//如果左半部分存在那么就消除下半部分
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_left;
		}
		else
		{
			//左半部分不在证明全部玩完了
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_no;
		}
		break;
	case D_DOWN:
		if (flag[D_UP])
		{
			//如果上半部分存在那么就消除下半部分
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_down;
		}
		else
		{
			//上半部分不在证明全部玩完了
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_no;
		}
		break;
	case D_RIGHT:
		if (flag[D_LEFT])
		{
			//如果右半部分存在那么就消除下半部分
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_right;
		}
		else
		{
			//右半部分不在证明全部玩完了
			map[Mpos.r][Mpos.c] = map[Mpos.r][Mpos.c] & Wall_no;
		}
		break;
	default:
		break;
	}
}

void Map::DestoryHome()
{
	for (int c = 0; c < 2; c++)
	{
		for (int r = 0; r < 2; r++)
		{
			map[Home_pos.r + r][Home_pos.c + c] = Home_Die_LU + r + c;
		}
	}

}

/*get函数*/
const uc(*Map::GetPos())[map_row_px][map_col_px]
{
	return &map;
}

uc Map::GetMPos(const Map_pos& Mpos)const
{
	return map[Mpos.r][Mpos.c];
}

int Map::GetMPos2(const Map_pos& Mpos)const {
	return map2[Mpos.r][Mpos.c];
}

/*set函数*/
void Map::SetMPos(const Map_pos& Mpos, uc mpos)
{
	map[Mpos.r][Mpos.c] = mpos;
}

void Map::SetMPos2(const Map_pos& Mpos, int mpos)
{
	map2[Mpos.r][Mpos.c] = mpos;
}