#include "Picture.h"

Picture::Picture() {


	//设置窗口
	initgraph(window_width, window_height);//定义窗口大小
	//整个标题
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("Tanks War"));

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
	loadimage(&tmpe, _T("PNG"), _T("TANK"), Dcount * sour_unit_px * 2, Campcount * sour_unit_px * 4, true);//4为4种坦克类型，由于没有对图片进行删减，所以选择手动填4
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

	//加载地图图片
	loadimage(&tmpe, _T("PNG"), _T("MAP"), FMcount * sour_map_px, sour_map_px, true);
	for (int i = 0; i < FMcount; i++) {
		int x = i * sour_map_px;//左上角x值
		int y = 0;//左上角y值
		getimage(MapPic + i, x, y, sour_map_px, sour_map_px);
	}
	cleardevice();//清空对象

	//加载子弹图片
	loadimage(&tmpe, _T("PNG"), _T("BULLET"), Dcount * sour_bullet_px, sour_bullet_px, true);
	for (int i = 0; i < Dcount; i++) {
		int x = i * sour_bullet_px;//左上角x值
		int y = 0;//左上角y值
		getimage(BulletPic + i, x, y, sour_bullet_px, sour_bullet_px);
	}
	cleardevice();//清空对象

	//加载家的图片
	loadimage(&tmpe, _T("PNG"), _T("HOME"), Statecount * sour_unit_px, sour_unit_px, true);
	for (int i = 0; i < Statecount; i++) {
		int x = i * sour_unit_px;//左上角x值
		int y = 0;//左上角y值
		getimage(HomePic + i, x, y, sour_unit_px, sour_unit_px);
	}
	cleardevice();//清空对象
}

Picture::~Picture()
{
	EndBatchDraw();//结束批量绘图模式
	closegraph();//关闭绘图界面
}

/*绘制图片*/


void Picture::half_transimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)//半透明化贴纸
{
	//初始化变量
	DWORD* dst = GetImageBuffer(dstimg);//获取绘画窗口指针
	DWORD* src = GetImageBuffer(srcimg);//获取图片指针
	int sour_src_width = srcimg->getwidth();
	int sour_src_height = srcimg->getheight();
	int sour_dst_width = (dstimg == NULL ? 0 : dstimg->getwidth());
	int sour_dst_height = (dstimg == NULL ? 0 : dstimg->getheight());

	//计算贴图区域的参数
	int dst_width = (x + sour_src_width * multiple_px > sour_dst_width) ? sour_dst_width - x : sour_src_width * multiple_px;//处理超出右边界
	int dst_height = (x + sour_src_height * multiple_px > sour_dst_height) ? sour_dst_height - x : sour_src_height * multiple_px;//处理超出下边界
	if (x < 0)//处理超出左边界
	{
		src += -x / multiple_px;
		dst_width -= x;
		x = 0;
	}
	if (y < 0)//处理超出上边界
	{
		src += (-y / multiple_px) * sour_src_width;
		dst_height -= y;
		y = 0;
	}
	dst += sour_dst_width * y + x;//修正目标贴图区起始位置

	//实现透明贴纸
	for (int sy = 0; sy < dst_height / multiple_px; sy++)
	{
		for (int sx = 0; sx < dst_width / multiple_px; sx++)
		{
			/*以下来自网络*/
			//取出素材数据
			int sa = ((src[sx] & 0xff000000) >> 24);
			int sr = ((src[sx] & 0xff0000) >> 16);	// 源值已经乘过了透明系数
			int sg = ((src[sx] & 0xff00) >> 8);		// 源值已经乘过了透明系数
			int sb = src[sx] & 0xff;				// 源值已经乘过了透明系数
			//接下来处理绘图显存，把每个源的像素，扩充到目标绘图区中，放大数倍
			for (int dy = 0; dy < multiple_px; dy++)//一个像素绘制多行
			{
				for (int dx = 0; dx < multiple_px; dx++)//一个像素绘制多列
				{
					//计算实际绘图的RGB色
					int dr = ((dst[dy * dst_width + dx] & 0xff0000) >> 16);
					int dg = ((dst[dy * dst_width + dx] & 0xff00) >> 8);
					int db = dst[dy * dst_width + dx] & 0xff;
					//应用到目标显存中
					dst[dy * dst_width + dx] = ((sr + dr * (255 - sa) / 255) << 16)
						| ((sg + dg * (255 - sa) / 255) << 8)
						| (sb + db * (255 - sa) / 255);
				}
			}
			dst += multiple_px;//修正目标绘图区到下一个位置
		}
		//进行下一行的绘制
		dst += multiple_px * sour_dst_width - dst_width;
		src += sour_src_width;
	}
	
}

void Picture::drawTank(const Tank& tank)//绘制坦克
{
	Draw_pos pos = tank.GetPosXY();//获取坐标
	UnitType type = tank.GetType();//获取类型
	Direction dir = tank.GetDirection();//获取方向
	TankCamp camp = type == computer ? Tank_computer : Tank_player;//判断阵营
	half_transimage(NULL, pos.x,pos.y,&TankPic[camp][dir][tank.GetTrackState()]);
}


void Picture::drawMap(const uc(*map)[map_row_px][map_col_px])//绘制地图
{
	for (int c = 0; c < map_row_px; c++)
	{
		for (int r = 0; r < map_col_px; r++) 
		{
			char temp = (*map)[c][r];
			switch (temp)
			{
			case Wall:
				putimage(r * sour_map_px, c * sour_map_px, MapPic + FM_wall);
				break;
			case Iron:
				putimage(r * sour_map_px, c * sour_map_px, MapPic + +FM_iron);
				break;
			case Border:
				putimage(r * sour_map_px, c * sour_map_px, MapPic + +FM_border);
				break;
			case Water:
				putimage(r * sour_map_px, c * sour_map_px, MapPic + +FM_water);
				break;
			//无冰面
			//jungle另弄一个弄一个函数,否则坦克会在丛林上面
			case Home_Live_LU:
				half_transimage(NULL, r * map_px, c * map_px, HomePic + HomeLive);
				break;
			case Home_Die_LU:
				half_transimage(NULL, r * map_px, c * map_px, HomePic + Homeover);
				break;
			default:
				break;
			}
			if (temp<Wall && temp>Empty)//绘制残缺的砖块
			{
				putimage(r * sour_map_px, c * sour_map_px, MapPic + FM_wall);//先绘制一个地图，然后再裁减
				for (int dc = 0; dc < 2; dc++)
				{
					for (int dr = 0; dr < 2; dr++)
					{
						if (!(temp & 1))//如果末尾为0
						{
							int up = c * sour_map_px + dc * sour_map_px / 2;
							int left = r * sour_map_px + dr * sour_map_px / 2;
							int down = c * sour_map_px + (dc + 1) * sour_map_px / 2;
							int right = r * sour_map_px + (dr + 1) * sour_map_px / 2;
							clearrectangle(left, up, right, down);//擦除不存在的砖
						}
						temp >>= 1;
					}
				}
			}
		}
	}
	drawInformation();
}

void Picture::drawJungle(const uc(*map)[map_row_px][map_col_px])//绘制丛林
{
	for (int r = 0; r < map_row_px; r++)
	{
		for (int c = 0; c < map_col_px; c++)
		{
			char temp = (*map)[r][c];
			if (temp == Jungle)
			{
				half_transimage(NULL, c * map_px, r * map_px, MapPic + FM_jungle);
			}
		}
	}
}

void Picture::drawInformation()
{

}