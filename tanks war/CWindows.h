#pragma once
#include <vector>
#include "AllSettings.h"
#include "Picture.h"
#include "Player.h"
#include "Map.h"
#include "bullet.h"
#include "time.h"


class CWindows
{
private:
	Picture pictures;//图像
	Map map;//地图
	Player play1;//玩家
	vector<Bullet> bullet;
	int play_bullet;
	const int bullet_cd = 100;
	
	bool game_state;//游戏状态

protected:
	void renwePicture();//刷新游戏页面
	void renewStart();//刷新开始游戏页面
	void controlUnit(Unit& unit, Map& map);//控制函数
	void shoot(const Unit& tank);//射击函数
	void renewBullet();//更新子弹的状态
	void destoryWall(const Bullet& bullet);//改变地形

public:
	CWindows();

	void Loadgame();//进入游戏
	void Playgame();//玩游戏

};

