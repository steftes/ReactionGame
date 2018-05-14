#include <wiringPi.h>
#include <iostream>
#include "Player.h"

Player::Player() = default;


void Player::read_name() 
{
	std::string name;
	std::cin >> name;
	name_ = name;
}

std::string Player::get_name() 
{
	return name_;
}