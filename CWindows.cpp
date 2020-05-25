﻿#include <iostream>
#include"map.h"
#include "CWindows.h"
#include"Unit.h"
using namespace std;

CWindows::CWindows()
{
	game_state = true;
	time::inittimer();
}


void CWindows::Loadgame()
{
	//renewStart();
	while (true)
	{
		if (KEY_DOWN(K_ESC))//查看是否按下退出键
		{
			HWND esc = GetHWnd();
			int button = MessageBox(esc, _T("是否要退出游戏？"), _T("退出游戏"), MB_YESNO | MB_ICONQUESTION);
			if (button == IDYES)
			{
				break;
			}
			if (button == IDNO)
			{
				time::resysclk();
			}
		}

		//if (game_state == false) {
		//	HWND choose = GetHWnd();
		//	int button = MessageBox(choose, _T("复活？"), _T("退出游戏"), MB_YESNO | MB_ICONQUESTION);
		//	if (button == IDYES) {
		//		time::resysclk();
		//		CWindows* playthegame = new CWindows;
		//		playthegame->Loadgame();
		//		delete playthegame;	
		//	}
		//	if (button == IDNO) {
		//		break;
		//	}
		//}
		Playgame();

		time::GameSleep(renewtime);

	}
}

void CWindows::Playgame()
{
	Unit* unit = &play1;
	static DWORD pic_time = time::Gettime();
	DWORD now = time::Gettime();

	if (game_state)
	{
		if (KEY_DOWN(K_PAUSE))//查看是否按下暂停键
		{
			HWND pause = GetHWnd();
			int button = MessageBox(pause, _T("是否要继续游戏？"), _T("继续游戏"), MB_YESNO | MB_ICONQUESTION);
			time::resysclk();
		}
		//控制玩家
		unit = &play1;
		if (unit)
		{
			if (unit->to_next())
			{
				controlUnit(*unit, map);//查看是否按下动作键
			}
		}
		//控制敌军
		for (int i = 0; i < armynum; i++)
		{
			unit = &army[i];
			if (unit)
			{
				if (unit->to_next())
				{
					Direction dir = unit->GetDirection();
					Direction dir1 = army[i].ai_move(dir, map);
					bool flag = army[i].ai_shoot(dir1);
					conrrolArmy(*unit, map, dir1, flag);
				}
			}
		}
		renewBullet();
	}
	cleardevice();//清屏
	renwePicture();//更新图片
	FlushBatchDraw();//显示
	checklevel();
}

void CWindows::renwePicture()
{
	pictures.drawMap(map.GetPos());//绘制地图
	for (int n = 0; n < armynum + 1; n++)
	{
		if (!bullet[n].empty())//绘制子弹
		{
			for (int i = 0; i < bullet[n].size(); i++)
			{
				pictures.drawBullet(bullet[n][i]);
			}
		}
	}
	pictures.drawTank(play1);//绘制坦克，用于绘制所有坦克
	for (int i = 0; i < armynum; i++)
	{
		pictures.drawTank(army[i]);//绘制敌人
	}
	pictures.drawJungle(map.GetPos());//绘制丛林
	pictures.drawBoom();//绘制爆炸效果
}

void CWindows::renewStart()
{
	RECT rect;//一个矩形
	rect = { 0,16 * sour_map_px,sour_window_width - 1,(16 + 3) * sour_map_px - 1 };
	drawtext(_T("按F进入坦克！"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//设置显示内容单行、水平垂直居中
}

void CWindows::controlUnit(Unit& unit, Map& map)
{
	Direction key_state;//保存
	int flag = 0;
	Map_pos mpos = unit.GetPosMap();
	vector<Map_pos>::iterator it;
	for (it = t.begin(); it != t.end(); it++) {
		if (*it==mpos) {
			it = t.erase(it);
			maptank.map2[mpos.c][mpos.r] = 0;
			break;
		}
	}
	if (KEY_DOWN(K_UP))
	{
		key_state = D_UP;
		flag++;
	}
	if (KEY_DOWN(K_LEFT))
	{
		key_state = D_LEFT;
		flag++;
	}
	if (KEY_DOWN(K_DOWN))
	{
		key_state = D_DOWN;
		flag++;
	}
	if (KEY_DOWN(K_RIGHT))
	{
		key_state = D_RIGHT;
		flag++;
	}
	if (flag == 1)
	{
		unit.move(key_state, map);//移动坦克
	}
	mpos = unit.GetPosMap();
	t.push_back(mpos);//更新坦克位置
	if (unit.GetType() == computer) maptank.map2[mpos.r][mpos.c] = computer;
	else if (unit.GetType() == player) maptank.map2[mpos.r][mpos.c] = player;

	//发射子弹
	if (KEY_DOWN(K_SHOOT))
	{
		static DWORD shoot_time = time::Gettime() - bullet_cd;
		DWORD now = time::Gettime();
		if (now - shoot_time >= bullet_cd)
		{
			shoot_time = now;
			shoot(unit);
		}
	}
}

void CWindows::conrrolArmy(Unit& unit, Map& map,Direction dir, bool ai_shoot)
{
	if (dir != D_STOP)
	{
		unit.move(dir, map);
	}
	if (ai_shoot)
	{
		static DWORD shoot_time = time::Gettime() - bullet_cd;
		DWORD now = time::Gettime();
		if (now - shoot_time >= bullet_cd)
		{
			shoot_time = now;
			shoot(unit);
		}
	}
}

void CWindows::shoot(const Unit& tank)
{
	if (tank.GetType() == player)
	{
		if (play_bullet >= max_num_bullets) return;
		play_bullet++;
		bullet[0].push_back(Bullet(tank));
	}

	//敌人坦克射击

	if (tank.GetType() == computer)
	{
		if (army_bullet[0] >= max_num_bullets) return;
		army_bullet[0]++;
		bullet[1].push_back(Bullet(tank));
	}
}
void CWindows::renewBullet()
{
	for (int i = 0; i < armynum + 1; i++)
	{
		if (!bullet[i].empty())
		{
			for (auto it = bullet[i].begin(); it != bullet[i].end();)
			{
				if (it->to_next())
				{
					if (it->move(it->GetDirection(), map))//如果子弹有碰撞
					{
						if (it->getowner() == player)
						{
							play_bullet--;
						}
						if (it->getowner() == computer)
						{
							army_bullet[i - 1]--;
						}
						destoryWall(*it);
						pictures.addboom(it->GetBoomPos());
						it = bullet[i].erase(it);
						continue;
					}
				}
				it++;
			}
		}
	}
}
void CWindows::destoryWall(const Bullet& bullet)
{
	Destoryunit destory = justsoso;
	ui paly = bullet.getowner();
	Direction dir = bullet.GetDirection();

	const Map_pos(*pos)[mcount] = bullet.GetCPos();
	const uc (*val)[mcount] = bullet.GetCVal();
	const bool(*flags)[lcount][mcount] = bullet.GetTouch();

	//触碰边界就退出
	if (map.GetMPos((*pos)[0]) == Border)
	{ 
		return;
	}

	bool first_wall = false;//查看第一层是否碰撞
	bool home_alive = false;//记录家的状态

	for (size_t l = 0; l < 2 && !first_wall; l++)//两层砖
	{
		for (size_t m = 0; m < 2; m++)//区分两块砖
		{
			if ((*val)[m] > Empty && (*val)[m] <= Border)//判断能否消除
			{
				if ((*flags)[l][m] == true)//发生碰撞
				{
					first_wall = true;//如果第一层发生碰撞，则不再往下消除
					map.DestroyMap((*pos)[m], dir, destory);
				}
			}
			if (!home_alive && (*val)[m] >= Home_Live_LU && (*val)[m] <= Home_Live_RD)
			{
				home_alive = true;
				map.DestoryHome();
				//复活
				

				//添加爆炸效果
				Draw_pos boom_pos = { (float)(Home_pos.c - 1) * map_px,(float)(Home_pos.r - 1) * map_px };
				//偏移爆炸点
				int leave_pos[2] = { 0 };//坐标偏移量
				int leave_dir[2] = { 0 };//方向偏移量
				for (size_t i = 0; i < 2; i++)
				{
					leave_pos[i] = rand() % (sour_map_px / 2) * multiple_px;
					leave_dir[i] = rand() % 3 - 1;
				}
				boom_pos.x += leave_dir[0] * leave_pos[0];
				boom_pos.y += leave_dir[1] * leave_pos[1];
				pictures.addboom(boom_pos, true);
			}
		}
	}
}

void CWindows::checklevel()//判断关卡状态
{
	//if (!pictures.getHome())
	//{
	//	map.ChangeLevel(++Level);
	//	pictures.setHome(true);
	//	return;
	//	显示下一关
	//}
	//敌人数为0
	//游戏失败
	if (!pictures.getHome()) {

	}
}
