#pragma once
#include "AllSettings.h"
#include "Unit.h"

class Tank :public Unit
{
private:
	bool Trackdisplay;//切换履带使用
	DWORD time_Trackdisplay;//履带切换时间点
	//int Tankspeed;//记录坦克类的速度
public:
	Tank(UnitType type, Direction direction, Map_pos pos);

	/*get函数*/
	bool GetTrackState()const;//获取履带状态
	//int GetTankspeed()const;//获取坦克速度

	/*控制函数*/
	virtual bool move(Direction direction, const Map& map);//坦克移动

};

