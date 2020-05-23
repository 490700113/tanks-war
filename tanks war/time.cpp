#include"time.h"
LARGE_INTEGER time::clk = { 0 };
ll time::oldclk = 0;
int time::freq = 0;
ll time::sysclk = 0;
ll time::gameclk = 0;

void time::Sleep(int ms) {
	if (oldclk == 0) {
		QueryPerformanceCounter(&clk);
		oldclk = clk.QuadPart;//获得开始时钟
	}
	int c = ms * freq;
	oldclk += c;
	QueryPerformanceCounter(&clk);
	if (clk.QuadPart > oldclk) oldclk = clk.QuadPart;
	else do {
		::Sleep(1);//延时
		QueryPerformanceCounter(&clk);//获得终止时钟
	} while (clk.QuadPart < oldclk);
}

void time::inittimer() {
	QueryPerformanceFrequency(&clk);
	freq = (int)clk.QuadPart / 1000;//获取计数器时钟频率
	resysclk();
}

void time::GameSleep(int ms) {
	Sleep(ms);
	QueryPerformanceCounter(&clk);//刷新一次游戏实际经过的周期数
	gameclk += clk.QuadPart - sysclk;
	resysclk();//延时后刷新一次系统周期数，便于之后时间统计
}

DWORD time::Gettime() {
	return (DWORD)gameclk / freq;
}

void time::resysclk() {
	QueryPerformanceCounter(&clk);
	sysclk = clk.QuadPart;
}