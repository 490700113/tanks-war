#include <iostream>
#include"map.h"
#include "CWindows.h"
#include"Unit.h"
#include"Player.h"
#include"Tank.h"
using namespace std;

CWindows::CWindows()
{
	game_state = false;
	time::inittimer();
	//Map_pos a;
	//a.r = 26, a.c = 10;
	//army[0].type = player;
	//army[0].SetPosMap(a);
	//army[0].life = 3;
	//army[0].SetDirection(D_UP);
	//a.r = 2, a.c = 2;
	//for (int i = 1; i < armynum+1; i++) {
	//	army[i].type = player;
	//	army[i].SetPosMap(a);
	//	army[i].life = 1;
	//	army[i].SetDirection(D_DOWN);
	//}
}

void CWindows::Loadgame()
{
	while (true)
	{
		if (!game_state)
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
		}
		else
		{
			if (KEY_DOWN(K_ESC))//查看是否按下退出键
			{
				HWND esc = GetHWnd();
				int button = MessageBox(esc, _T("是否要返回主菜单？"), _T("退出游戏"), MB_YESNO | MB_ICONQUESTION);
				if (button == IDYES)
				{
					game_state = 0;
				}
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

	cleardevice();//清屏

	if (game_state)
	{
		//renewBullet();
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
				if(play1.life!=0) controlUnit(*unit, map);//查看是否按下动作键
			}
		}

		renewBullet();
		//控制敌军
		for (int i = 0; i < armynum; i++)
		{
			if (army[i].life == 0) continue;
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
		renwePicture();//更新图片
		checklevel();
	}
	else
	{
		renewStart();
	}
	FlushBatchDraw();//显示
}


void CWindows::renewStart()
{
	if (KEY_DOWN(K_UP))
	{
		if (choosemodel > 0)
		{
			choosemodel--;
		}
	}
	Sleep(100);
	if (KEY_DOWN(K_DOWN))
	{
		if (choosemodel < 2)
		{
			choosemodel++;
		}
	}
	pictures.drawStart(choosemodel);
	if (KEY_DOWN(K_IN))
	{
		if (choosemodel == 0)
		{
			canmove = 1;
			bullet_cd = 100;
			max_num_bullets = 2;
			mod = 1;
			enemyleft = 10;
			play1.life = 3;
			map.ChangeLevel(Level);
		}
		if (choosemodel == 1)
		{
			canmove = 1;
			bullet_cd = 100;
			max_num_bullets = 2;
			mod = 1;//无界模式记得改一下，QAQ
			enemyleft = 10;
			play1.life = 3;
			map.ChangeLevel(Level);
		}
		if (choosemodel == 2)
		{
			canmove = 0;
			bullet_cd = 50;
			max_num_bullets = 10;
			mod = 1;
			enemyleft = 10;
			play1.life = 3;
			map.ChangeLevel(Level);
		}
		game_state = true;
	}
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
	if(play1.life) pictures.drawTank(play1);//绘制坦克，用于绘制所有坦克
	for (int i = 0; i < armynum; i++)
	{
		if(army[i].life) pictures.drawTank(army[i]);//绘制敌人
	}

	pictures.drawJungle(map.GetPos());//绘制丛林
	pictures.drawBoom();//绘制爆炸效果
	pictures.drawInformation(Level,enemyleft,play1.life);
}

void CWindows::controlUnit(Unit& unit, Map& map)
{
	Direction key_state;//保存
	int flag = 0;
	Map_pos mpos = unit.GetPosMap();
	//play1.SetPosMap({ 0,0 });

	//else
	//{
	//	for (int i = 0; i < armynum ; i++) {
	//		if (army[i].GetPosMap() == mpos) {
	//			army[i].SetPosMap({ 0,0 });
	//			map.map2[mpos.r][mpos.c] = 0;
	//		}
	//	}
	//}

	//for (int i = 0; i < armynum+1;i++) {
	//	if (army[i].GetPosMap()==mpos) {
	//		if (army[i].GetType() == player) {
	//			army[i].life--;
	//			Map_pos a;
	//			a.r = 26, a.c = 10;
	//			army[i].SetPosMap(a);
	//			map.map2[26][10] = 1;
	//		}
	//		else if (army[i].GetType() == computer) {
	//			if (armynum < enemyleft) army[i].life = 0;
	//			Map_pos a;
	//			a.r = 2, a.c = 2;
	//			army[i].SetPosMap(a);
	//			map.map2[2][2] = 1;
	//		}
	//		map.map2[mpos.c][mpos.r] = 0;
	//		break;
	//	}
	//}
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
	if (flag == 1 && canmove ==1)
	{
		unit.move(key_state, map);//移动坦克
	}
	map.map2[mpos.r][mpos.c] = 0;
	mpos = unit.GetPosMap();
	play1.SetPosMap(mpos);
	//for(int i=0;i<30;i++)
	//	for (int j = 0; j < 32; j++) {
	//		map.map2[i][j] = 0;
	//	}

	//Map_pos mpos = play1.GetPosMap();
	map.map2[mpos.r][mpos.c] = 1;


	//if (unit.GetType() == computer) map.map2[mpos.r][mpos.c] = computer;
	//else if (unit.GetType() == player) map.map2[mpos.r][mpos.c] = player;

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
	Map_pos mpos = unit.GetPosMap();
	//for (int i = 0; i < armynum ; i++) {
	//	if (army[i].GetPosMap() == mpos) {
	//		army[i].SetPosMap({ 0,0 });
	//		//map.map2[mpos.r][mpos.c] = 0;
	//	}
	//}
	/*for (int i = 0; i < armynum+1;i++) {
		if (army[i].GetPosMap() == mpos) {
			if (army[i].GetType() == player) {
				Map_pos a;
				a.r = 26, a.c = 10;
				army[i].SetPosMap(a);
				map.map2[26][10] = 1;
			}
			else if (army[i].GetType() == computer) {
				if (armynum < enemyleft) army[i].life = 0;
				Map_pos a;
				a.r = 2, a.c = 2;
				army[i].SetPosMap(a);
				map.map2[2][2] = 1;
			}
			map.map2[mpos.c][mpos.r] = 0;
			break;
		}
	}*/
	if (dir != D_STOP)
	{
		unit.move(dir, map);
	}
	map.map2[mpos.r][mpos.c] = 0;
	mpos = unit.GetPosMap();
	Map_pos cmp = { 0,0 };
	for (int i = 0; i < armynum ; i++) {
		if (army[i].GetPosMap() == cmp) {
			army[i].SetPosMap(mpos);
			break;
		}
	}
	//for (int i = 0; i < 30; i++)
	//	for (int j = 0; j < 32; j++) {
	//		map.map2[i][j] = 0;
	//	}
	for (int i = 0; i < armynum;i++) {
		Map_pos mpos = army[i].GetPosMap();
		map.map2[mpos.r][mpos.c] = 1;
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

	if (tank.GetType() == computer)
	{	
		int no;
		//敌人坦克射击
		Map_pos pos = tank.GetPosMap();
		for (no = 0; no < armynum; no++)
		{
			if (pos == army[no].GetPosMap())
				break;
		}

		if (army_bullet[no] >= max_num_bullets) return;
		army_bullet[no]++;
		no++;
		bullet[no].push_back(Bullet(tank));
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
						Map_pos cmp = (*it).GetPosMap();
						if (play1.GetPosMap() == cmp)   //碰到我们自己
						{
							map.map2[cmp.r][cmp.c] = 0;
							play1.life--;
							Map_pos a;
							a.r = 26, a.c = 10;
							play1.rebronset(a, D_DOWN);
						//	map.map2[26][10] = 1;
						}

						int last = 0;
						for (int j = 0; j < armynum; j++) //统计存活坦克数
						{
							if (army[j].life) last++;
						}

						for (int j = 0; j < armynum; j++) {
							if (cmp == army[j].GetPosMap()) {
								map.map2[cmp.r][cmp.c] = 0;
								enemyleft--;
								if (enemyleft - last < 0) army[j].life = false;
								Map_pos a;
								a.r = 2, a.c = 2;
								army[i].rebronset(a,D_UP);
							//	map.map2[2][2] = 1;
								break;
								//for (int i = 0; i < armynum; i++) {
								//	Map_pos cmpp = army[i].GetPosMap();
								//	if (cmpp == cmp) {
								//		Map_pos a;
								//		a.r = 2, a.c = 2;
								//		if (armynum < enemyleft) army[i].life = 0;
								//		army[i].SetPosMap(a);
								//		map.map2[2][2] = 1;
								//		break;
								//	}
								//}
								//if (play1.GetPosMap() == cmp) {
								//	play1.life--;
								//	play1.generateplayer();
								//}
								//for (int k = 0; k < armynum; k++) {
								//	if (army[k].GetPosMap() == cmp) {
								//		enemyleft--;
								//		army[k].life = false;
								//		map.map2[cmp.r][cmp.c] = 0;
								//		break;
								//	}
								//}
							}
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
	if (!pictures.getHome() || play1.life == 0) {
		game_state = false;
		pictures.setHome(true);
		pictures.fail();
		FlushBatchDraw();//显示
		Sleep(1000);
	}
	if (enemyleft == 0)
	{
		enemyleft = 10;
		play1.life = 3;
		play1.rebronset({ 26,10 },D_UP);
		for (int i = 0; i < armynum; i++)
		{
			army[i].life = true;
		}
		Level++;
		Level = Level % max_level + 1;
		map.ChangeLevel(Level);
		pictures.win();
		FlushBatchDraw();//显示
		Sleep(1000);
	}

}

