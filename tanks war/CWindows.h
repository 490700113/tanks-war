#pragma once
#include <vector>
#include "AllSettings.h"
#include "Picture.h"
#include "Player.h"
#include "AI_army.h"
#include "Map.h"
#include "bullet.h"
#include "time.h"
//#include"Tank.h"

class CWindows
{
private:
	Picture pictures;//图像
	Map map;//地图
	Player play1;//玩家
	AI_army army[armynum];//敌军
	vector<Bullet> bullet[armynum+1];
	int play_bullet;
	int army_bullet[armynum];
	int bullet_cd = 100;
	int enemyleft = 10;
	int Level = 1;//关卡数
	bool game_state;//游戏状态
	int choosemodel = 0;//模式选择
	int canmove = 1;//堡垒模式，能否移动
	int mod = 1;//无界模式，用于边界取模
	int max_num_bullets = 2;//子弹存在的上限

protected:
	void renwePicture();//刷新游戏页面
	void renewStart();//刷新开始游戏页面
	void controlUnit(Unit& unit, Map& map);//控制函数
	void conrrolArmy(Unit& unit, Map& map, Direction dir, bool ai_shoot);//控制敌人
	void shoot(const Unit& tank);//射击函数
	void renewBullet();//更新子弹的状态
	void destoryWall(const Bullet& bullet);//改变地形
	void checklevel();//判断关卡状态

public:
	CWindows();
	Tank t[armynum+1];//存坦克数组
	//Map maptank;//另开一张图存坦克坐标
	void Loadgame();//进入游戏
	void Playgame();//玩游戏
};

