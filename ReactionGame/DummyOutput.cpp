#include "DummyOutput.h"
#include <wiringPi.h>
#include <iostream>

Dummy_output::Dummy_output(bool initial_state /* = false */) : out_state_{ initial_state }
{
}

void Dummy_output::turn_on(int led)
{
	if (out_state_) 
	{
		return;
	}

	pinMode(led, OUTPUT);
	digitalWrite(led, HIGH);

	out_state_ = true;
}

void Dummy_output::turn_off(int led)
{
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);

	out_state_ = false;
}

bool Dummy_output::out_state() const {
	return out_state_;
}