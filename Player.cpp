#include "Player.h"


Player::Player(UnitType type, Map_pos pos, Direction direction)
	:Tank(type, pos, direction)
{
}

//Player Player::generateenemy() {
//	Map_pos a;
//	a.r = 2, a.c = 2;
//	Player* newtank = new Player(computer, a, D_DOWN);
//	return *newtank;
//}
//
//Player Player::deletetank(Player &p) {
//	p.life = 0;
//}
//
//Player Player::generateplayer(int lifee) {
//	Map_pos a;
//	a.r = 26, a.c = 10;
//	Player* newtank = new Player(computer, a, D_UP);
//	newtank->life = lifee;
//	return *newtank;
//}

float Player::getspeed()const
{
	return Movespeed / 1000.0f;
}