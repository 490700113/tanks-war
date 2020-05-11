#pragma once
#include <cmath>
#include <graphics.h>



/*�궨��*/
#define KEY_DOWN(VK_NONAME) (GetAsyncKeyState(VK_NONAME) & 0x8000) //������⣬�Ƿ񱻰���



/*���ڲ���*/
const int multiple_px = 3;//�Ŵ���  --�����ʾ����ȫ���߹�С�����ʵ�����

//��ͼ���ص�����
const int map_row_px = 30;//����x--��
const int map_col_px = 32;//����y--��

//ԭʼ��ֽ�����ش�С   --sourԭʼ
const int sour_map_px = 8; //ԭ��ͼ��Ԫ��Ӧ�����ش�С
const int sour_unit_px = sour_map_px * 2;//ÿ����Ԫ��̹�ˡ����ߵȣ�ԭʼ�زĵ����ش�С
const int sour_boom_px = sour_unit_px * 2;//��ը��ͼ�����ؿ��
const int sour_bullet_px = sour_map_px / 2;//�ӵ�ԭʼ�زĵ����ش�С

//��ʾʱ��ͼ�����ش�С
const int map_px = multiple_px * sour_map_px;//��ʾʱÿ����ͼ��Ԫ��С
const int unit_px = map_px * 2;//̹�ˡ����ߵĴ�С
const int boom_px = unit_px * 2;//ʵ�ʱ�ը��С
const int bullet_px = map_px / 2;//�ӵ���С

//ԭʼ��Ϸ��������ؿ�͸�
const int sour_window_width = sour_map_px * map_row_px;//ԭʼ��Ϸ���ڿ�
const int sour_window_height = sour_map_px * map_col_px;//ԭʼ��Ϸ���ڸ�

//��Ϸ��������ؿ�͸�
const int window_width = map_px * map_row_px;//��ʵ��Ϸ���ڿ�
const int window_height = map_px * map_col_px;//��ʵ��Ϸ���ڸ�

//��Ԫ����Ĵ�С���Ա㽫һ�����طֳɸ�С�ĵ�Ԫ
const int unit_row_px = map_row_px * 2;//��Ԫ��
const int unit_col_px = map_col_px * 2;//��Ԫ��
const int unit_size = 4;//������Ԫ��С
const int bullet_size = unit_size / 2;//�ӵ���Ԫ��С
const int map_size = unit_size / 2;//��ͼ��Ԫ��С



/*��ͼ������*/
typedef struct
{
	int x, y;
}postion_xy;



/*��Ϸ��ʼҳ����ʾ*/



/*���ʵ�����*/
const int renewtime = 1000 / 60;//����ˢ������
int speed = (int)(3.5 * map_size * map_px) * renewtime;//ÿ����3.5���



/*��Ԫ��ز���*/
//��ֽ����
enum maptype//��ͼ����
{
	Empty,//�յ�
	Wall = 0x0F,//ש��
	Iron,//���� --0x10(up) or 0x20(down)
	Jungle = 0x22,//����
	Border,//��ͼ�߽�
	Home//0xC8��0xC9��0xCA��0xCB�ֱ����ҵ����ϡ����¡����ϡ�����
};

//��Ԫ����
enum unittype
{
	player = 300,
	computer = 400,
	bullet = 500,
	home = 0xC8
};

//����
enum direction//����
{
	D_UP,D_LEFT,D_DOWN,D_RIGHT
};

//��������
enum keycin
{
	K_UP = 'W',K_LEFT = 'A',K_DOWN = 'S',K_RIGHT = 'D',K_SHOOT = 'J',
	K_PAUSE = 'P',K_ESC = VK_ESCAPE
};



/*��ȡָ��ģ���е���Դ�ļ�*/
// ������
//		strDstFile:		Ŀ���ļ�������ȡ����Դ�����������
//		strResType:		��Դ���ͣ�
//		strResName:		��Դ���ƣ�
// ����ֵ��
//		true: ִ�гɹ���
//		false: ִ��ʧ�ܡ�
//bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);