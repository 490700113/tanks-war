#pragma once
#include"Unit.h"
#include"AllSettings.h"

enum MapLayer {//ÿ��ש��������
	firl, secl, lcount
};

enum MapIndex {//�ڵ����������ש
	firm, secm, mcount
};

enum corner {//ÿ��ש��Ϊ4������
	ul = 0xf1, ur = 0xf2, dl = 0xf4, dr = 0xf8
};

class Bullet : public Unit{
	public:
		Bullet(const Unit& tank);
		virtual bool move(Direction dir, const Map& map);//�ӵ���ǰ�ƶ�������������ײ�ͷ���true
		virtual float getspeed()const;//����ƶ��ٶ�
		virtual bool touch(const Map& map);//�Ƿ���ײ
		unsigned int getowner()const;//��ȡ�ӵ�������

		const Map_pos(*GetCheckPointsPos() const)[mcount];//��ȡ��������
		const char(*GetChectPointsVal() const)[mcount];//��ȡ�����ֵ
		const bool(*GetTouchFlags() const)[lcount][mcount];//��ȡ������ײ���
		virtual const Draw_pos GetBoomXYPos()const;//��ȡ��ը��ͼ����

	protected:
		void recheckpoint(const Map& map);//ˢ�¼���
		void recheckpos();//ˢ�¼�������
		void recheckval(const Map& map);//ˢ�¼�����ֵ
		void retouchflag();//ˢ����ײ�����
	private:
		UnitType owner;//˭����
		Map_pos chechpos[mcount];//��������
		char checkval[mcount];//��������
		bool flag[lcount][mcount];//������ײ��ǣ��ڵ�����ײ������ͼ��λ��ÿ����ͼ��λֻ��ײһ�����䣩
};