
#include "Input.h"
#include "piproxy.h"
#include <iostream>
#include <chrono>


extern int64_t start_time_us;  // MFA start time should probably be passed to buttonIsr as a parameter // STEFAN ? 

Input::Input() 
{
	in_value_ = 0;
}

bool Input::read(int pin)
{
	pinMode(pin, INPUT);  // MFA this should be done once in the ctor, not on every read. but then you would need to have pin as a member variable // STEFAN?
	in_value_ = digitalRead(pin);
	return in_value_;
}

void Input::init(int pin)
{
	pinMode(pin, INPUT);  // MFA pin should be a member variable, init should happen in the constructor /// STEFAN ?
	pullUpDnControl(pin, PUD_OFF);
}

bool Input::last_state()
{
	return in_value_;
}

void Input::buttonISR()
{
	button_ = true; 
	auto now = std::chrono::system_clock::now().time_since_epoch();
	auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

	time_ = delta;
}

bool Input::get_button()
{
	return button_;
}

int Input::time_point()
{
	return time_;
}

void Input::buttonISR_reset()
{
	button_ = false; 
}