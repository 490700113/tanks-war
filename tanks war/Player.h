#pragma once
#include "Tank.h"

const Draw_pos P_bron_pos = { 26,10 };

class Player :public Tank
{
private:
	//IMAGE img[0][4][2]; //加载图片  就是想看看怎么贴图
public:
	Player(UnitType type = player, Direction direction = D_UP, Draw_pos pos = P_bron_pos);

	////显示
	//void show()
	//{
	//	paint_pos pos = GetPosXY();
	//	putimage(pos.x, pos.y, &img[0][GetDirection()][0], SRCPAINT);
	//};

	//void load()     //加载图片没填完的坑
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (size_t j = 0; j < 2; j++)
	//		{
	//		}
	//	}
	//}
};

