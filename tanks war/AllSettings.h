#pragma once
#include <cmath>
#include <graphics.h>



/*宏定义*/
#define KEY_DOWN(VK_NONAME) (GetAsyncKeyState(VK_NONAME) & 0x8000) //按键检测，是否被按下



/*窗口参数*/
const int multiple_px = 3;//放大倍数  --如果显示不完全或者过小可以适当调整

//地图像素的行列
const int map_row_px = 30;//像素x--行
const int map_col_px = 32;//像素y--列

//原始贴纸的像素大小   --sour原始
const int sour_map_px = 8; //原地图单元对应的像素大小
const int sour_unit_px = sour_map_px * 2;//每个单位（坦克、道具等）原始素材的像素大小
const int sour_boom_px = sour_unit_px * 2;//爆炸贴图的像素宽度
const int sour_bullet_px = sour_map_px / 2;//子弹原始素材的像素大小

//显示时贴图的像素大小
const int map_px = multiple_px * sour_map_px;//显示时每个地图单元的实际像素大小
const int unit_px = map_px * 2;//坦克、道具的绘图大小
const int boom_px = unit_px * 2;//实际爆炸贴图大小
const int bullet_px = map_px / 2;//子弹绘图大小

//原始游戏界面的像素宽和高
const int sour_window_width = sour_map_px * map_row_px;//原始游戏窗口宽
const int sour_window_height = sour_map_px * map_col_px;//原始游戏窗口高

//游戏界面的像素宽和高
const int window_width = map_px * map_row_px;//真实游戏窗口宽
const int window_height = map_px * map_col_px;//真实游戏窗口高

//单元数组的大小，以便将一个像素分成更小的单元
const int unit_row_px = map_row_px * 2;//单元行
const int unit_col_px = map_col_px * 2;//单元列
const int unit_size = 4;//基础单元大小
const int bullet_size = unit_size / 2;//子弹单元大小
const int map_size = unit_size / 2;//地图单元大小



/*游戏开始页面显示*/


/*速率的设置*/
const int renewtime = 1000 / 60;//画面刷新周期
