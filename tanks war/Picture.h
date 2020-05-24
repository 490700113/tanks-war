#pragma once
#include "AllSettings.h"
#include "Tank.h"
#include "Map.h"
#include "bullet.h"
#include<vector>
using std::vector;
#define ull unsigned long long 
/*爆炸参数*/
const int boomcount = 5;//爆炸贴图总数目
const int smallcount = 3;//小爆炸贴图数目
const int bigcount = boomcount;//大爆炸贴图数目
const int showtime = 90;//每张图片显示时间
const int smalltime = showtime * smallcount;//小爆炸持续的时间
const int bigtime = showtime * bigcount;//大爆炸持续的时间
typedef struct {
	int picnum;//爆炸点所用贴图数目
	int time;//爆炸持续时间
	DWORD nowtime;//这次爆炸的时间
	Draw_pos pos;//爆炸点坐标
}boomnode;


class Picture
{
private:
	IMAGE TankPic[Campcount][Dcount][2];//坦克图片//想搞类型在camp和d中间加一维
	IMAGE MapPic[FMcount];//地图图片
	IMAGE BulletPic[Dcount];//子弹图片
	IMAGE HomePic[Statecount];//家图片
	IMAGE BoomPic[5];//爆炸图片
	IMAGE logo;

	float bkcolor[3];//背景颜色
	float chacolor[3];//文字颜色
	vector<boomnode>points;//爆炸点数据

	bool home_state = true;//家的状态

protected:
	// 半透明贴图函数
	// 参数：
	//		dstimg：目标 IMAGE（NULL 表示默认窗体）
	//		x, y:	目标贴图位置
	//		srcimg: 源 IMAGE 对象指针
	//void half_transimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);//半透明贴纸

	void half_transimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg); 
	//void Inf_half_transimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);//用于信息描绘
	void reboompoint();//刷新爆炸点
	void fill(IMAGE& dstimg, const IMAGE& srcimg);//用一个图像填充另一个

public:
	Picture();
	~Picture();

	/*绘制图形*/
	void drawMap(const uc(*map)[map_row_px][map_col_px]);//绘制地图
	void drawTank(const Tank& tank);//绘制坦克
	void drawJungle(const uc(*map)[map_row_px][map_col_px]);//绘制丛林
	void drawBullet(Bullet& bullet);//绘制子弹
	void drawBoom();//绘制爆炸
	void drawInformation(int l);//绘制信息
	void addboom(const Draw_pos& pos, bool flag = false);//新增爆炸点,false小爆炸,true带爆炸
	//void rebcolor();//变化背景颜色
	//void reeffect();//转换图片颜色

	/*get函数*/
	bool getHome()const;
	/*set函数*/
	void setHome(const bool setflag);
};

