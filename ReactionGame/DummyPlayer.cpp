#include <wiringPi.h>
#include <iostream>
#include "IPlayer.h"
#include "DummyPlayer.h"

Dummy_player::Dummy_player()
{
}

void Dummy_player::name()
{
	std::string name;
	std::cin >> name;
	name_ = name;
}

std::string Dummy_player::give_name()
{
	return name_;
}