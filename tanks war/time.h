#pragma once
#include<Windows.h>
#define ll long long
#define ull unsigned long long 
class time {//以下（包括time.cpp)来源自互联网，以用来解决时间获取问题和暂停时时间计算等问题
	private:
		static LARGE_INTEGER clk;//时钟信息
		static ll oldclk;//开始时钟和结束时钟
		static int freq;//时钟频率
		static ll sysclk;//循环开始时要刷新这个变量
		static ll gameclk;//实际游戏经过的周期数（排除了暂停时间）
	public:
		static void Sleep(int ms);
		static void inittimer();//初始化时间
		static void GameSleep(int ms);//游戏专用延迟(参数false即表示没暂停)
		static DWORD Gettime();//获取现在已经经过的时间
		static void resysclk();//刷新游戏循环开始前的系统周期数
};