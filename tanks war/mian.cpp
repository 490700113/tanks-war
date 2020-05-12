#include <Windows.h>
#include "AllSettings.h"
#include "Player.h"

int main()
{
	Player P1;

	initgraph(window_width,window_height);

	while(1)   //想尝试先贴个坦克上去看看能不能跑
	{
		if (KEY_DOWN(K_DOWN))
		{
			paint_pos pos = P1.GetPosXY();
			pos.y++;
			P1.SetPosXY(pos);
		}
	}
}