#include "Pin_control.h"
#include <wiringPi.h>
#include <iostream>


Pin_control::Pin_control() = default;

Pin_control::~Pin_control()
{
}

void Pin_control::read_pin()
{
	int pin_to_control;
	std::cin >> pin_to_control;
	pin_to_control_ = pin_to_control;
}

int Pin_control::get_pin()
{
	return pin_to_control_;
}