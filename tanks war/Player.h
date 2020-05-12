#pragma once
#include "Tank.h"

const paint_pos P_bron_pos = { 26,10 };

class Player :public Tank
{
private:
	IMAGE img[0][4][2];
public:
	Player(UnitType type = player, Direction direction = D_UP, paint_pos pos = P_bron_pos);

	//œ‘ æ
	void show()
	{
		paint_pos pos = GetPosXY();
		putimage(pos.x, pos.y, &img[0][GetDirection()][0], SRCPAINT);
	};

	void load()
	{
		for (int i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
			}
		}
	}
};

