#include "Tank.h"


Tank::Tank(UnitType type, Direction direction, paint_pos pos)
	:Unit(type, direction, pos)
{

}

/*get����*/
bool Tank::GetTrackState() const//��ȡ�Ĵ�״̬
{
	return Trackdisplay;
}
int Tank::GetTankspeed() const//��ȡ̹���ٶ�
{
	return Tankspeed;
}

/*���ƺ���*/
bool Tank::move(Direction direction, const Map& map)//̹���ƶ�
{

}