#include <iostream>
#include "CWindows.h"
using namespace std;

CWindows::CWindows()
{
	game_state = true;
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
		}

		Playgame();

	}
}

void CWindows::Playgame()
{
	Unit* unit = &play1;

	if (game_state)
	{
		if (KEY_DOWN(K_PAUSE))//查看是否按下暂停键
		{
			HWND pause = GetHWnd();
			int button = MessageBox(pause, _T("是否要继续游戏？"), _T("继续游戏"), MB_YESNO | MB_ICONQUESTION);
		}
		controlUnit(*unit, map);//查看是否按下动作键
	}
	//cleardevice();//清屏
	//清屏好像有问题
	renwePicture();//更新图片
}

void CWindows::renwePicture()
{
	pictures.drawMap(map.GetPos());//绘制地图
	pictures.drawTank(play1);//绘制坦克，用于绘制所有坦克
	pictures.drawJungle(map.GetPos());//绘制丛林
}

void CWindows::renewStart()
{

}

void CWindows::controlUnit(Unit& unit, Map& map)
{
	Direction key_state;//保存
	int flag = 0;
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

	//发射子弹
	if (KEY_DOWN(K_SHOOT))
	{
		static ull shoot_time = time::Gettime() - bullet_cd;
		ull now = time::Gettime();
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
	}
	bullet.push_back(Bullet(tank));
}
void CWindows::renewBullet()
{
	if (!bullet.empty())
	{
		for (auto it = bullet.begin(); it != bullet.end(); it++)
		{
			if (it->to_next())
			{
				if (it->move(it->GetDirection(), map))//如果子弹有碰撞
				{
					if (it->getowner() == player)
					{
						play_bullet--;
					}
					destoryWall(*it);
					pictures.addboom(it->GetBoomPos());
					it = bullet.erase(it);
					it--;
				}
			}
		}
	}
}
void CWindows::destoryWall(const Bullet& bullet)
{

}