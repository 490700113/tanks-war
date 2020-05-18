#pragma once
#include "AllSettings.h"
#include "Tank.h"
#include "Map.h"


/*爆炸参数*/
//晚点填坑


class Picture
{
private:
	IMAGE TankPic[Campcount][Dcount][2];//坦克图片//想搞类型在camp和d中间加一维
	IMAGE MapPic[FMcount];//地图图片
	IMAGE BulletPic[Dcount];//子弹图片
	IMAGE HomePic[Statecount];//家图片
	//IMAGE BoomPic[];//爆炸图片//后期整

protected:
	// 半透明贴图函数
	// 参数：
	//		dstimg：目标 IMAGE（NULL 表示默认窗体）
	//		x, y:	目标贴图位置
	//		srcimg: 源 IMAGE 对象指针
	void half_transimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);//半透明贴纸

public:
	Picture();
	~Picture();

	/*绘制图形*/
	void drawMap(const uc(*map)[map_row_px][map_col_px]);//绘制地图
	void drawTank(const Tank& tank);//绘制坦克
	void drawJungle(const uc(*map)[map_row_px][map_col_px]);//绘制丛林
	void drawInformation();//绘制信息
};

