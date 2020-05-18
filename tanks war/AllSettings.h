#pragma once
#include <math.h>
#include <graphics.h>



/*宏定义*/
#define KEY_DOWN(VK_NONAME) (GetAsyncKeyState(VK_NONAME) & 0x8000) //按键检测，是否被按下
#define uc unsigned char

/*窗口参数*/
const int multiple_px = 3;//放大倍数  --如果显示不完全或者过小可以适当调整

//地图像素的行列
const int map_row_px = 30;//像素x--行
const int map_col_px = 32;//像素y--列

//原始贴纸的像素大小   --sour原始
const int sour_map_px = 8; //原地图单元对应的像素大小
const int sour_unit_px = sour_map_px * 2;//每个单元（坦克、道具等）原始素材的像素大小
const int sour_boom_px = sour_unit_px * 2;//爆炸贴图的像素宽度
const int sour_bullet_px = sour_map_px / 2;//子弹原始素材的像素大小

//显示时贴图的像素大小
const int map_px = multiple_px * sour_map_px;//显示时每个地图单元大小
const int unit_px = map_px * 2;//坦克、道具的大小
const int boom_px = unit_px * 2;//实际爆炸大小
const int bullet_px = map_px / 2;//子弹大小

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



/*绘图的坐标*/
typedef struct
{
	int x, y;
}Draw_pos;

//行列坐标
typedef struct
{
	int r, c;
}Map_pos;


/*游戏开始页面显示*/



/*速率的设置*/
const int renewtime = 1000 / 60;//画面刷新周期
const int Movespeed = (int)(3.5 * map_size * map_px) * renewtime;//每秒走3.5大格



/*单元相关参数*/
//贴纸代码
enum MapType//地图类型
{
	Empty = 0x00,//空地
	Wall = 0x0F,//砖块
	Iron = 0x10,//铁块
	Water = 0x12,//水面
	Jungle = 0x22,//丛林
	Border = 0x11,//地图边界
	//0xC8、0xC9、0xCA、0xCB分别代表家的左上、左下、右上、右下
	Home_Live_LU = 0xC8,
	Home_Live_LD = 0xC9,
	Home_Live_RU = 0xCA,
	Home_Live_RD = 0xCB,
	Home_Die_LU = 0xCC,
};

//单元类型
enum UnitType
{
	player = 300,
	bullet = 500,
	computer = 600,
	home = 0xC8
};

//方向
enum Direction//方向
{
	D_UP,D_LEFT,D_DOWN,D_RIGHT,Dcount
};

//键盘输入
enum KeyCin
{
	K_UP = 'W',K_LEFT = 'A',K_DOWN = 'S',K_RIGHT = 'D',K_SHOOT = 'J',
	K_PAUSE = 'P',K_ESC = VK_ESCAPE
};

enum MapNum//地图类型
{
	FM_wall, FM_iron, FM_border, FM_water, FM_no_use1, FM_no_use2, FM_jungle, FMcount
};

enum TankCamp//坦克阵营
{
	Tank_player, Tank_computer, Campcount
};

enum HomeState//家的状态
{
	HomeLive, Homeover, Statecount
};


//以下参考自网络
/*提取指定模块中的资源文件*/
// 参数：
//		strDstFile:		目标文件名。提取的资源将保存在这里；
//		strResType:		资源类型；
//		strResName:		资源名称；
// 返回值：
//		true: 执行成功；
//		false: 执行失败。
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);