#include "bullet.h"

Bullet::Bullet(const Unit& tank) :
	Unit(tank.GetMapPos(), bullet, tank.GetDirection()), owner(tank.GetType()) {
	Map_pos unitpos = tank.GetUnitPos();//���������unit���꣨�������������
	Draw_pos pxpos = GetPosXY();//��������Ļ�ͼ����
	//���������ӵ�����
	switch (GetDirection()) {
		case UP:
			unitpos.c++;
			//pxpos.x=(float)unitpos.c*
				//�����Ȳ�д�� ����̫��㲻�����������Ū�����������
	}
}