#pragma once
#include"Unit.h"
#include"AllSettings.h"

enum MapLayer {//每块砖看成两层
	firl, secl, lcount
};

enum MapIndex {//炮弹会击中两块砖
	firm, secm, mcount
};

enum corner {//每块砖分为4个角落
	ul = 0xf1, ur = 0xf2, dl = 0xf4, dr = 0xf8
};

class Bullet : public Unit{
	public:
		Bullet(const Unit& tank);
		virtual bool move(Direction dir, const Map& map);//子弹向前移动，发生地形碰撞就返回true
		virtual float getspeed()const;//获得移动速度
		virtual bool touch(const Map& map);//是否碰撞
		unsigned int getowner()const;//获取子弹所有者

		const Map_pos(*GetCheckPointsPos() const)[mcount];//获取检查点坐标
		const char(*GetChectPointsVal() const)[mcount];//获取检查点的值
		const bool(*GetTouchFlags() const)[lcount][mcount];//获取地形碰撞标记
		virtual const Draw_pos GetBoomXYPos()const;//获取爆炸贴图坐标

	protected:
		void recheckpoint(const Map& map);//刷新检查点
		void recheckpos();//刷新检查点坐标
		void recheckval(const Map& map);//刷新检查点数值
		void retouchflag();//刷新碰撞检查标记
	private:
		UnitType owner;//谁射♂的
		Map_pos checkpos[mcount];//检查点坐标
		char checkval[mcount];//检查点数据
		bool flag[lcount][mcount];//地形碰撞标记（炮弹会碰撞两个地图单位，每个地图单位只碰撞一个角落）
};