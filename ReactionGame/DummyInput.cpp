
#include "DummyInput.h"
#include <wiringPi.h>
#include <iostream>
#include <chrono>


extern int64_t start_time_us;

Dummy_input::Dummy_input()
{
}

bool Dummy_input::read(int pin)
{
	pinMode(pin, INPUT);
	in_value_ = digitalRead(pin);
	return in_value_;
}

void Dummy_input::init(int pin)
{
	pinMode(pin, INPUT);
	pullUpDnControl(pin, PUD_OFF);
}

bool Dummy_input::last_state()
{
	return in_value_;
}
// aso hallo
void Dummy_input::buttonISR()
{
	button_ = 1;
	auto now = std::chrono::system_clock::now().time_since_epoch();
	auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

	time_ = delta;
}

bool Dummy_input::button()
{
	return button_;
}

int Dummy_input::time()
{
	return time_;
}

void Dummy_input::buttonISR_reset()
{
	button_ = 0;
}
