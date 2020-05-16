#pragma once
#include "AllSettings.h"
#include "Picture.h"
#include "Player.h"
#include "Map.h"



class Windows
{
private:
	Picture pictures;//图像
	Map map;//地图
	Player play1;//玩家
	
	bool game_state;//游戏状态

protected:
	void renwePicture();//刷新游戏页面
	void renewStart();//刷新开始游戏页面
	void controlUnit(Unit& unit, Map& map);//控制函数
//	void shoot();//射击函数

public:
	Windows();

	void Loadgame();//进入游戏
	void Playgame();//玩游戏

};

