#include "Picture.h"

Picture::Picture() {


	//设置窗口
	initgraph(window_width, window_height);//定义窗口大小
	//整个标题
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("tlstxdy"));

	//设置窗口居中
	//获取屏幕大小
	int scrwidth = GetSystemMetrics(SM_CXSCREEN);
	int scrheight = GetSystemMetrics(SM_CYSCREEN);
	//获取窗口大小
	RECT rect;//定义一个矩形
	GetWindowRect(hWnd, &rect);
	//设置rect的值
	rect.left = (scrwidth - rect.right + rect.left) / 2;
	rect.top = (scrheight - rect.bottom + rect.top) / 2;//原版为3
	//移动窗口到中间
	SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom, SWP_NOSIZE);

	/*加载图片*/
	IMAGE tmpe;//临时对象
	SetWorkingImage(&tmpe);//设置当前绘图设备
	//加载坦克图片
	loadimage(&tmpe, _T("PNG"), _T("TANK"), Dcount * sour_unit_px * 2, Tankcount * sour_unit_px * 4, true);//4为4种坦克类型，由于没有对图片进行删减，所以选择手动填4
	for (int camp = 0; camp < Campcount; camp++)//阵营
	{
		for (int dir = 0; dir < Dcount; dir++)//方向
		{
			for(int trackn = 0; trackn < 2; trackn++)//履带
			{
				int x = (dir * 2 + trackn) * sour_unit_px;//左上角x值
				int y = (camp * 4) * sour_unit_px;//左上角y值，4位装甲数
				getimage(&TankPic[camp][dir][trackn], x, y, sour_unit_px, sour_unit_px);
			}
		}
	}
	cleardevice();//清空对象


}