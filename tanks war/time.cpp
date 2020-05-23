#include"time.h"
LARGE_INTEGER time::clk = { 0 };
ll time::oldclk = 0;
int time::freq = 0;
ll time::sysclk = 0;
ll time::gameclk = 0;

void time::Sleep(int ms) {
	if (oldclk == 0) {
		QueryPerformanceCounter(&clk);
		oldclk = clk.QuadPart;//��ÿ�ʼʱ��
	}
	int c = ms * freq;
	oldclk += c;
	QueryPerformanceCounter(&clk);
	if (clk.QuadPart > oldclk) oldclk = clk.QuadPart;
	else do {
		::Sleep(1);//��ʱ
		QueryPerformanceCounter(&clk);//�����ֹʱ��
	} while (clk.QuadPart < oldclk);
}

void time::inittimer() {
	QueryPerformanceFrequency(&clk);
	freq = (int)clk.QuadPart / 1000;//��ȡ������ʱ��Ƶ��
	resysclk();
}

void time::GameSleep(int ms) {
	Sleep(ms);
	QueryPerformanceCounter(&clk);//ˢ��һ����Ϸʵ�ʾ�����������
	gameclk += clk.QuadPart - sysclk;
	resysclk();//��ʱ��ˢ��һ��ϵͳ������������֮��ʱ��ͳ��
}

DWORD time::Gettime() {
	return (DWORD)gameclk / freq;
}

void time::resysclk() {
	QueryPerformanceCounter(&clk);
	sysclk = clk.QuadPart;
}