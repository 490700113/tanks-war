#pragma once
#include<Windows.h>
#define ll long long
#define ull unsigned long long 
class time {//���£�����time.cpp)��Դ�Ի����������������ʱ���ȡ�������ͣʱʱ����������
	private:
		static LARGE_INTEGER clk;//ʱ����Ϣ
		static ll oldclk;//��ʼʱ�Ӻͽ���ʱ��
		static int freq;//ʱ��Ƶ��
		static ll sysclk;//ѭ����ʼʱҪˢ���������
		static ll gameclk;//ʵ����Ϸ���������������ų�����ͣʱ�䣩
	public:
		static void Sleep(int ms);
		static void inittimer();//��ʼ��ʱ��
		static void GameSleep(int ms);//��Ϸר���ӳ�(����false����ʾû��ͣ)
		static ull Gettime();//��ȡ�����Ѿ�������ʱ��
		static void resysclk();//ˢ����Ϸѭ����ʼǰ��ϵͳ������
};