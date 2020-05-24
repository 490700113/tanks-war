#include "Player.h"


Player::Player(UnitType type, Map_pos pos, Direction direction)
	:Tank(type, pos, direction)
{
}

float Player::getspeed()const
{
	return Movespeed / 1000.0f;
}