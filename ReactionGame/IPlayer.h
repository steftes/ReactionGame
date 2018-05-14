#pragma once

#include <wiringPi.h>
#include <iostream>
#include <string>

class IPlayer {
public:
	virtual void name() = 0;

	virtual std::string give_name() = 0;

	// virtual destructor, as always!
	virtual ~IPlayer() = 0;
};