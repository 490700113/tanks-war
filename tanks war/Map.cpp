#include <iostream>
#include <fstream>
#include "Map.h"
#include "Picture.h"
using namespace std;

Map::Map()
{
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
	for (int r = 0; r < map_row_px; r++)
	{
		for (int c = 0; c < map_col_px; c++)
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

/*get函数*/
const char(*Map::GetMPos())[map_row_px][map_col_px]
{
	return &map;
}

char Map::GetMPos(const Map_pos& Mpos)const
{
	return map[Mpos.r][Mpos.c];
}

/*set函数*/
void Map::SetMPos(const Map_pos& Mpos, char mpos)
{
	map[Mpos.r][Mpos.c] = mpos;
}