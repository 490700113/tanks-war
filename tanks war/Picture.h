#pragma once
#include "AllSettings.h"
#include "Tank.h"
#include "Map.h"

enum MapNum//地图类型
{
	FM_wall,FM_iorn,FM_border,FM_water,FM_no_use1,FM_no_use2,FM_jungle,FMcount
};

enum TankCamp//坦克阵营
{
	Tank_player,Tank_computer,Campcount
};


/*爆炸参数*/
//晚点填坑


class Picture
{
private:
	IMAGE TankPic[Campcount][Dcount][2];//坦克图片//想搞类型在camp和d中间加一维
	IMAGE MapPic[FMcount];//地图图片
	IMAGE BulletPic[Dcount];//子弹图片
	//IMAGE BoomPic[];//爆炸图片//后期整
public:
	Picture();
	~Picture();

	/*绘制图形*/
	void drawTank(const Tank& tank);//绘制坦克


};

