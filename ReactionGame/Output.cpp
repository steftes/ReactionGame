#include "Output.h"
#include "piproxy.h"
#include <iostream>

Output::Output(bool initial_state /* = false */) : out_state_{ initial_state }
{
}

void Output::turn_on(int led)  // MFA this is rather buggy. if I call turn_on(4), then turn_on(5), the second call will be ignored because out_state is true
{  // MFA led should probably be a member.
	if (out_state_) 
	{
		return;
	}

	pinMode(led, OUTPUT);
	digitalWrite(led, HIGH);

	out_state_ = true;
}

void Output::turn_off(int led)
{ // MFA led should be a member. // Stefan Teschl: Why?
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);

	out_state_ = false;
}

bool Output::out_state() const {
	return out_state_;  // MFA you should call digitalRead here, the cached out_state_ can be wrong in many cases! also, which pin does it correspond to?
}