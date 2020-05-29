#pragma once
#include "AllSettings.h"
#include "Unit.h"

class Tank :public Unit
{
private:
	bool Trackdisplay;//切换履带使用
	DWORD time_Trackdisplay;//履带切换时间点
	const int max_life = 3;
	//int Tankspeed;//记录坦克类的速度
public:
	Tank(UnitType type, Map_pos pos, Direction direction = D_DOWN);
	Tank();
	int life;
	void generateenemy();
	void generateplayer();
    void deletetank(Tank &t);
	/*get函数*/

	bool GetTrackState()const;//获取履带状态
	//int GetTankspeed()const;//获取坦克速度
	void retrackstate();
	/*控制函数*/
	virtual bool move(Direction direction, const Map& map,int type);//坦克移动

};

